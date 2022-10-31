#include "glass.h"
#include <glm/gtc/random.hpp>

#define M_PI            3.14159265358979323846
#define M_2_PI          2.0 * M_PI

namespace rt::material {
    Glass::Glass(const glm::vec3& color) {
        this->color = color;
    }

    glm::vec3 Glass::interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, float& refractIdx, bool& isLightSource) {
        // Return tint
        isLightSource = false;
        tint = color;
        
        // Reflect
        float oldRef = refractIdx;
        refractIdx = (refractIdx == 1.52f) ? 1.0f : 1.52f;
        return glm::refract(in, norm, oldRef / refractIdx);
    }

    void Glass::setColor(const glm::vec3& color) {
        this->color = color;
    }
}