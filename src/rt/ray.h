#pragma once
#include "../glm/glm.hpp"

namespace rt {
    struct Ray {
        glm::vec3 org;
        glm::vec3 dir;
    };
}