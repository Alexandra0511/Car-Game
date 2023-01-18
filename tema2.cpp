#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/obiecte3D.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

//float FoV = glm::radians(85.0f);
//float width = 0.0f;

void Tema2::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    renderCameraTarget = false;

    camera = new implemented::Camera2();
    tx = 1.0f;
    tz = 3.71f;
    angle = 0;
    radius = 0.1f;
    carCenter = glm::vec3(0, 0, 0);

    camera->Set(carCenter + glm::vec3(-camera->distanceToTarget, 0.5f, 0), carCenter, glm::vec3(0, 1, 0));
    
    // resetare in functie de pozitia masinii
    tx = camera->GetTargetPosition().x;
    tz = camera->GetTargetPosition().z;
    

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    Mesh* tree = obiecte3D::CreateTree("tree");
    meshes["tree"] = tree;

    Mesh* car = obiecte3D::CreateCar("car", glm::vec3(0, 0, 0), 0.3f, 0.1f, 0.1f, glm::vec3(1, 0, 0));
    meshes["car"] = car;

    Mesh* car2 = obiecte3D::CreateCar("car2", glm::vec3(0, 0, 0), 0.3f, 0.1f, 0.1f, glm::vec3(1, 1, 0));
    meshes["car2"] = car2;

    Mesh* car3 = obiecte3D::CreateCar("car3", glm::vec3(0, 0, 0), 0.3f, 0.1f, 0.1f, glm::vec3(0, 1, 1));
    meshes["car3"] = car3;

    Mesh* car4 = obiecte3D::CreateCar("car4", glm::vec3(0, 0, 0), 0.3f, 0.1f, 0.1f, glm::vec3(1, 0, 1));
    meshes["car4"] = car4;

    Mesh* grass = obiecte3D::CreateGrass("grass");
    meshes["grass"] = grass;

    Mesh* track = obiecte3D::CreateTrack("track", outerPoints, innerPoints, outerTree, innerTree, mid, car2T, car3T);
    meshes["track"] = track;

    // indicii de plecare a obstacolelor masini
    idx1 = 2;
    pos1 = mid[2];

    idx2 = 6;
    pos2 = car2T[idx2];

    idx3 = 16;
    pos3 = car3T[idx3];

    tx = mid[0].x;
    tz = mid[0].z;
    angle = atan2((mid[mid.size() - 1].x - mid[0].x), (mid[mid.size() - 1].z - mid[0].z)) + RADIANS(90);


    carCenter = glm::vec3(tx, 0.2f, tz);

    // setarea camerei dupa masina
    camera->Set(carCenter + glm::vec3(camera->distanceToTarget, 0.5f, 0), carCenter, glm::vec3(0, 1, 0));
    camera->RotateThirdPerson_OY(angle);
    glm::vec3 p = camera->GetTargetPosition();

    tx = p.x;
    tz = p.z;

}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.529f, 0.807f, 0.980f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

bool Tema2::Collision(glm::vec3 point) {
    float f = sqrt((point.x - tx) * (point.x - tx) + (point.z - tz) * (point.z - tz));
    if (f <= 2 * radius)
        return true;
    return false;
}

void Tema2::RenderScene()
{
    // pista
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
    RenderMesh(meshes["track"], shaders["VertexColor"], modelMatrix);

    // iarba
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
    RenderMesh(meshes["grass"], shaders["VertexColor"], modelMatrix);

    // masina
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(tx, 0.05f, tz));
    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
    RenderMesh(meshes["car"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < outerTree.size(); i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, outerTree[i]);
        RenderMesh(meshes["tree"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < innerTree.size(); i++) {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, innerTree[i]);
        RenderMesh(meshes["tree"], shaders["VertexColor"], modelMatrix);
    }

    
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }

    // prima masina obstacol cu traiectoria si viteza sa proprie
    {
        idx1 = idx1 % mid.size();

        int plus1 = idx1 + 1;
        glm::vec3 A = mid[idx1];
        plus1 = plus1 % mid.size();
        glm::vec3 B = mid[plus1];
        glm::vec3 dreapta = B - A;
        float distance = 0.025f;
        glm::vec3 dir = glm::normalize(glm::vec3(dreapta.x, 0, dreapta.z));
        pos1 += dir * distance;
        if (glm::length(B - pos1) < 0.05f) {
            idx1 += 1;
            idx1 = idx1 % mid.size();
            pos1 = mid[idx1];
        }
        idx1 = idx1 % mid.size();
        
        float angle2 = atan2((B.x - A.x), (B.z - A.z)) - RADIANS(90);
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(pos1.x, 0.05f, pos1.z));
        modelMatrix = glm::rotate(modelMatrix, angle2, glm::vec3(0, 1, 0));
        RenderMesh(meshes["car2"], shaders["VertexColor"], modelMatrix);
    }

    // a doua masina obstacol cu traiectoria si viteza sa proprie
    {
        idx2 = idx2 % car2T.size();
        int plus2 = idx2 + 1;
        glm::vec3 A = car2T[idx2];
        plus2 = plus2 % car2T.size();
        glm::vec3 B = car2T[plus2];
        glm::vec3 dreapta = B - A;
        float distance = 0.02f;
        glm::vec3 dir = glm::normalize(glm::vec3(dreapta.x, 0, dreapta.z));
        pos2 += dir * distance;
        if (glm::length(B - pos2) < 0.05f) {
            idx2 += 1;
            idx2 = idx2 % car2T.size();
            pos2 = car2T[idx2];
        }
        idx2 = idx2 % car2T.size();
        float angle2 = atan2((B.x - A.x), (B.z - A.z)) - RADIANS(90);
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(pos2.x, 0.05f, pos2.z));
        modelMatrix = glm::rotate(modelMatrix, angle2, glm::vec3(0, 1, 0));
        RenderMesh(meshes["car3"], shaders["VertexColor"], modelMatrix);
    }

    // a treia masina obstacol cu traiectoria si viteza sa proprie
    {
        idx3 = idx3 % car3T.size();
        int plus3 = idx3 + 1;
        glm::vec3 A = car3T[idx3];
        plus3 = plus3 % car3T.size();
        glm::vec3 B = car3T[plus3];
        glm::vec3 dreapta = B - A;
        float distance = 0.01f;
        glm::vec3 dir = glm::normalize(glm::vec3(dreapta.x, 0, dreapta.z));
        pos3 += dir * distance;
        if (glm::length(B - pos3) < 0.05f) {
            idx3 += 1;
            idx3 = idx3 % car3T.size();
            pos3 = car3T[idx3];
        }
        idx3 = idx3 % car3T.size();
        float angle2 = atan2((B.x - A.x), (B.z - A.z)) - RADIANS(90);
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(pos3.x, 0.05f, pos3.z));
        modelMatrix = glm::rotate(modelMatrix, angle2, glm::vec3(0, 1, 0));
        RenderMesh(meshes["car4"], shaders["VertexColor"], modelMatrix);
    }
  
}

void Tema2::Update(float deltaTimeSeconds)
{

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);
    //camera->Set(pos, center, up);
    RenderScene();

    glm::vec3 pos = camera->position;
    glm::vec3 up = camera->up;
    glm::vec3 right = camera->right;
    glm::vec3 forward = camera->forward;
    float distToTarget = camera->distanceToTarget;
    glm::vec3 targetPos = camera->GetTargetPosition();
    targetPos.y = 0;

    glClear(GL_DEPTH_BUFFER_BIT);
    

    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    projectionMatrix = glm::ortho(-8.f, 8.f, -5.f, 5.f, 0.0f, 90.0f);
    camera->Set(targetPos + glm::vec3(-1, 5, 1), targetPos, glm::vec3(0, 1, 0));

    RenderScene();

    camera->up = up;
    camera->right = right;
    camera->forward = forward;
    camera->distanceToTarget = distToTarget;
    camera->position = pos;
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::FrameEnd()
{
   // DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


bool SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b) {
    if (glm::dot(glm::cross(b - a, p1 - a), glm::cross(b - a, p2 - a)) >= 0) {
        return true;
    }
    return false;
}

bool PointInT(glm::vec3 point, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    if (SameSide(point, a, b, c) && SameSide(point, b, a, c) && SameSide(point, c, a, b)) {
        return true;
    }
    return false;
}

bool Tema2::IsInsideTrack(Mesh* track)
{
    int num_ver = track->vertices.size() / 2;

    for (int i = 0; i < num_ver; i++) {
        glm::vec3 point = glm::vec3(camera->GetTargetPosition().x, 0, camera->GetTargetPosition().z);
        if (PointInT(point, outerPoints[i], outerPoints[(i + 1) % num_ver], innerPoints[i]) ||
            PointInT(point, innerPoints[i], innerPoints[(i + 1) % num_ver], outerPoints[(i + 1) % num_ver])) {
            return true;
        }
    }

    return false;
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 2.0f;

    if (window->KeyHold(GLFW_KEY_W)) {
        if (Collision(pos1)==false && Collision(pos2)==false && Collision(pos3)==false) {
            camera->MoveForward(deltaTime * cameraSpeed);

            tx = camera->GetTargetPosition().x;
            tz = camera->GetTargetPosition().z;
            if (!IsInsideTrack(meshes["track"]) == true) {
                camera->MoveForward(-deltaTime * cameraSpeed);

                tx = camera->GetTargetPosition().x;
                tz = camera->GetTargetPosition().z;
            }
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        renderCameraTarget = true;
        angle += deltaTime * 0.5f ;
        camera->RotateThirdPerson_OY(deltaTime * 0.5f );
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if (Collision(pos1) == false && Collision(pos2) == false && Collision(pos3) == false) {
            camera->MoveForward(-deltaTime * cameraSpeed);

            tx = camera->GetTargetPosition().x;
            tz = camera->GetTargetPosition().z;
            if (!IsInsideTrack(meshes["track"]) == true) {
                camera->MoveForward(deltaTime * cameraSpeed);

                tx = camera->GetTargetPosition().x;
                tz = camera->GetTargetPosition().z;
            }
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        renderCameraTarget = true;
        angle -= deltaTime * 0.5f ;
        camera->RotateThirdPerson_OY(-deltaTime * 0.5f );
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        camera->TranslateUpward(-0.1f);
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        camera->TranslateUpward(0.1f);
    }

}


void Tema2::OnKeyPress(int key, int mods)
{
    //if (key == GLFW_KEY_T)
    //{
    //    renderCameraTarget = !renderCameraTarget;
    //}

    //// Proiectie ortografica
    //if (key == GLFW_KEY_O)
    //{
    //    projectionMatrix = glm::ortho(-1, 1, -1, 1, 0, 100);
    //}

    //// Proiectie perspectiva
    //if (key == GLFW_KEY_P)
    //{
    //    projectionMatrix = glm::perspective(RADIANS(45), window->props.aspectRatio, 0.01f, 100.0f);
    //}
}


void Tema2::OnKeyRelease(int key, int mods)
{
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            
            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
