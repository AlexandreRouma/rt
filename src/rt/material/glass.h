#pragma once
#include <memory>
#include "../material.h"

namespace rt::material {
    class Glass : public Material {
    public:
        Glass(const glm::vec3& color);

        glm::vec3 interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, float& refractIdx, bool& isLightSource);

        void setColor(const glm::vec3& color);

    private:
        glm::vec3 color;
    };
}