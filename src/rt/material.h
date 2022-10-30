#pragma once
#include "ray.h"

namespace rt {
    class Material {
    public:
        virtual glm::vec3 interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, bool& isLightSource) = 0;
    };
}