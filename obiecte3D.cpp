#include "lab_m1/Tema2/obiecte3D.h"
#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"



Mesh* obiecte3D::CreateTree(
    const std::string& name)
{
    Mesh* treeObj = new Mesh(name);

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0, 0.2f), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0.2f, 0, 0.2f), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0, 0.4f, 0.2f), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0.2f, 0.4f, 0.2f), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0.2f, 0, 0), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0, 0.4f, 0), glm::vec3(0.36f, 0.25f, 0.2f)),
        VertexFormat(glm::vec3(0.2f, 0.4f, 0), glm::vec3(0.36f, 0.25f, 0.2f)),

        VertexFormat(glm::vec3(-0.2f, 0.4f, 0.4f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(-0.2f, 0.8f, 0.4f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(0.4f, 0.8f, 0.4f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(-0.2f, 0.4f, -0.2f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(0.4f, 0.4f, -0.2f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(-0.2f, 0.8f, -0.2f), glm::vec3(0, 0.152f, 0)),
        VertexFormat(glm::vec3(0.4f, 0.8f, -0.2f), glm::vec3(0, 0.152f, 0)),
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,

        8, 9, 10,
        9, 11, 10,
        10, 11, 15,
        10, 15, 14,
        9, 15, 11,
        9, 13, 15,
        14, 15, 12,
        15, 13, 12,
        8, 12, 9,
        9, 12, 13,
        10, 14, 12,
        8, 10, 12
    };

    treeObj->InitFromData(vertices, indices);
    return treeObj;
}

Mesh* obiecte3D::CreateGrass(
    const std::string& name)
{
    Mesh* grassObj = new Mesh(name);

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-25, -0.1f, 25), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(25, -0.1f, 25), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(25, -0.1f, -25), glm::vec3(0, 1, 0)),
        VertexFormat(glm::vec3(-25, -0.1f, -25), glm::vec3(0, 1, 0))
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        3, 0, 2
    };

    grassObj->InitFromData(vertices, indices);
    return grassObj;
}

Mesh* obiecte3D::CreateTrack(
    const std::string& name,
    std::vector<glm::vec3>& outer,
    std::vector<glm::vec3>& inner, 
    std::vector<glm::vec3>& outerTree, 
    std::vector<glm::vec3>& innerTree,
    std::vector<glm::vec3>& mid,
    std::vector<glm::vec3>& car2T,
    std::vector<glm::vec3>& car3T)
{
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-17.66f, 0, 5.44f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-14.44f, 0, 6.73f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-9.4f, 0, 7.69f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-3.92f, 0, 6.73f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(0.48f, 0, 4.04f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(4.83f, 0, 3.56f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(10.1f, 0, 5.1f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(12.82f, 0, 10.16f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(14.75f, 0, 10.91f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(18.78f, 0, 9.84f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(20.66f, 0, 7.59f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(22.27f, 0, 1.36f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(21.57f, 0, -3.9f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(20.01f, 0, -6.85f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(14.97f, 0, -8.19f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(6.7f, 0, -6.85f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(0, 0, -4.9f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-7.04f, 0, -6.85f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-10.95f, 0, -8.03f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-14.76f, 0, -7.17f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-17.02f, 0, -5.72f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-18.2f, 0, -3.95f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-19.54f, 0, -0.62f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(glm::vec3(-19.11f, 0, 3.19f), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0))
    };

    std::vector<VertexFormat> verticesInnerAndOuter;
    glm::vec3 D, P, R, A;

    float distRed = 0.5f;
    float distBlue = 0.6f;

    float distTreeExt = 0.9f;
    float distTreeInt = 1.0f;

    glm::vec3 color = glm::vec3(0.36f, 0.25f, 0.2f);
    glm::vec3 UP = glm::vec3(0, 1, 0);

    for (int i = 0; i < 23; i++) {
        D = vertices[i + 1].position - vertices[i].position;
        P = glm::normalize(glm::cross(D, UP));
        R = vertices[i].position + distRed * P;
        A = vertices[i].position - distBlue * P;
        mid.push_back(vertices[i].position);
        outerTree.push_back(vertices[i].position + distTreeExt * P);
        innerTree.push_back(vertices[i].position - distTreeInt * P);
        
        // punctele pentru traiectoriile masinilor obstacol
        car2T.push_back(vertices[i].position + 0.4f * P);
        car3T.push_back(vertices[i].position - 0.4f * P);

        // limitele de interior si exterior ale pistei
        inner.push_back(A);
        outer.push_back(R);

        // vector cu toate punctele delimitatoare ale pistei
        verticesInnerAndOuter.push_back(VertexFormat(A, color));
        verticesInnerAndOuter.push_back(VertexFormat(R, color));
    }
    // inserarea in vector si a ultimei pozitii
    mid.push_back(vertices[23].position);
    D = vertices[0].position - vertices[23].position;
    P = glm::normalize(glm::cross(D, UP));
    R = vertices[23].position + distRed * P;
    A = vertices[23].position - distBlue * P;
    
    outerTree.push_back(vertices[23].position + distTreeExt * P);
    innerTree.push_back(vertices[23].position - distTreeInt * P);

    car2T.push_back(vertices[23].position + 0.4f * P);
    car3T.push_back(vertices[23].position - 0.4f * P);

    inner.push_back(A);
    outer.push_back(R);

    verticesInnerAndOuter.push_back(VertexFormat(A, color));
    verticesInnerAndOuter.push_back(VertexFormat(R, color));

    Mesh* track = new Mesh("track");

    std::vector<unsigned int> indices;
    for (int i = 0; i < verticesInnerAndOuter.size(); i++) {
        indices.push_back(i);
    }
    indices.push_back(0);
    indices.push_back(1);

    track->SetDrawMode(GL_TRIANGLE_STRIP);

    track->InitFromData(verticesInnerAndOuter, indices);

    return track;
}

Mesh* obiecte3D::CreateCar(
    const std::string& name,
    glm::vec3 center,
    float length,
    float height,
    float width,
    glm::vec3 color)
{
    Mesh* carObj = new Mesh(name);

    std::vector<VertexFormat> vertices
    {
        VertexFormat(center + glm::vec3(-length / 2, -height / 2, width / 2), color),
        VertexFormat(center + glm::vec3(length / 2, -height / 2, width / 2), color),
        VertexFormat(center + glm::vec3(-length / 2, height / 2, width / 2), color),
        VertexFormat(center + glm::vec3(length / 2, height / 2, width / 2), color),
        VertexFormat(center + glm::vec3(-length / 2, -height / 2, -width / 2), color),
        VertexFormat(center + glm::vec3(length / 2, -height / 2, -width / 2), color),
        VertexFormat(center + glm::vec3(-length / 2, height / 2, -width / 2), color),
        VertexFormat(center + glm::vec3(length / 2, height / 2, -width / 2), color)
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4
    };

    carObj->InitFromData(vertices, indices);
    return carObj;
}

