#pragma once
#include <vector>
#include "../glm/glm.hpp"
#include "material.h"

namespace rt {
    class Object {
    public:
        virtual const std::vector<glm::vec3>& getVertices() = 0;
        virtual const std::vector<std::shared_ptr<Material>>& getMaterials() = 0;
        virtual const std::vector<glm::vec<4, int>>& getIndices() = 0;
    };
}