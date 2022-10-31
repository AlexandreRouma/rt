#pragma once
#include <memory>
#include "../material.h"

namespace rt::material {
    class LightSource : public Material {
    public:
        LightSource(const glm::vec3& color, float intensity);

        glm::vec3 interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, float& refractIdx, bool& isLightSource);

        void setColor(const glm::vec3& color);
        void setIntensity(float intensity);

    private:
        glm::vec3 color;
        float intensity;
        glm::vec3 tint;
    };
}