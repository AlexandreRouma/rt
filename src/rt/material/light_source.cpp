#include "light_source.h"

namespace rt::material {
    LightSource::LightSource(const glm::vec3& color, float intensity) {
        this->color = color;
        this->intensity = intensity;
        tint = color * intensity;
    }

    glm::vec3 LightSource::interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, bool& isLightSource) {
        tint = this->tint;
        isLightSource = true;
        return glm::vec3(0);
    }

    void LightSource::setColor(const glm::vec3& color) {
        this->color = color;
        this->tint = this->color * this->intensity;
    }

    void LightSource::setIntensity(float intensity) {
        this->intensity = intensity;
        this->tint = this->color * this->intensity;
    }
}