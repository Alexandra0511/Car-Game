#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         struct ViewportArea
         {
             ViewportArea() : x(0), y(0), width(1), height(1) {}
             ViewportArea(int x, int y, int width, int height)
                 : x(x), y(y), width(width), height(height) {}
             int x;
             int y;
             int width;
             int height;
         };

        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderScene();
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool IsInsideTrack(Mesh* track);
        bool Collision(glm::vec3 point);
     

     protected:
         implemented::Camera2* camera;
         implemented::Camera2* camera2;
         glm::mat4 projectionMatrix;
         bool renderCameraTarget;
         ViewportArea miniViewportArea;

         float tx, tz;
         float angle;
         glm::vec3 carCenter;
         std::vector<VertexFormat> verticesInnerAndOuter;

         std::vector<glm::vec3> innerPoints;
         std::vector<glm::vec3> outerPoints;
         std::vector<glm::vec3> outerTree;
         std::vector<glm::vec3> innerTree;
         glm::vec3 pos1, pos2, pos3;
         int idx1, idx2, idx3;
         std::vector<glm::vec3> mid, car2T, car3T;
         float radius;

    };
}   // namespace m1
