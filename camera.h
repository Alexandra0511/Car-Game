#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class Camera2
    {
     public:
        Camera2()
        {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            distanceToTarget = 1.f;
        }

        Camera2(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
        }

        ~Camera2()
        { }

        // Update camera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            forward     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            this->up    = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            position = position + forward * distance;
            /*glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;*/
        }

        void TranslateUpward(float distance)
        {
            // TODO(student): Translate the camera using the `up` vector.
            position = position + glm::normalize(up) * distance;
            /*glm::vec3 dir = glm::normalize(glm::vec3(0, up.y, up.z));
            position += dir * distance;*/

        }

        void TranslateRight(float distance)
        {
            position = position + glm::normalize(right) * distance;

        }

        void RotateFirstPerson_OX(float angle)
        {
            forward = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1),angle, right) * glm::vec4(forward, 1))));
            
            up = glm::normalize(glm::cross(right, forward));

        }

        void RotateFirstPerson_OY(float angle)
        {
            forward = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1))));
            right = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1))));
            up = glm::normalize(glm::cross(right, forward));

        }

        void RotateFirstPerson_OZ(float angle)
        {
            right = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1), angle, forward) * glm::vec4(right, 1))));
            up = glm::normalize(glm::cross(right, forward));

        }

        void RotateThirdPerson_OX(float angle)
        {
            position += forward * distanceToTarget;
            RotateFirstPerson_OX(angle);
            //TranslateForward(-distanceToTarget);
            position -= forward * distanceToTarget;

        }

        void RotateThirdPerson_OY(float angle)
        {
            // Rotate the camera in third-person mode around
            // the OY axis.
            TranslateForward(distanceToTarget);
            //position += forward * distanceToTarget;
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
            //position -= forward * distanceToTarget;

        }

        void RotateThirdPerson_OZ(float angle)
        {
            position += forward * distanceToTarget;
            RotateFirstPerson_OZ(angle);
            //TranslateForward(-distanceToTarget);
            position += forward * distanceToTarget;

        }

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

     public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace implemented
