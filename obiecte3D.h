#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace obiecte3D
{
    Mesh* CreateCar(const std::string& name, glm::vec3 center, float length, float height, float width, glm::vec3 color);
    Mesh* CreateTree(const std::string& name);
    Mesh* CreateGrass(const std::string& name);
    //Mesh* CreateTrack(const std::string& name);
    Mesh* CreateTrack(const std::string& name, std::vector<glm::vec3>& outer, std::vector<glm::vec3>& inner, std::vector<glm::vec3>& outerTree,
        std::vector<glm::vec3>& innerTree, std::vector<glm::vec3>& mid, std::vector<glm::vec3>& car2T, std::vector<glm::vec3>& car3T);
}
#pragma once
