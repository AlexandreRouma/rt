#include "mirror.h"
#include <glm/gtc/random.hpp>

#define M_PI            3.14159265358979323846
#define M_2_PI          2.0 * M_PI

namespace rt::material {
    Mirror::Mirror(const glm::vec3& color) {
        this->color = color;
    }

    glm::vec3 Mirror::interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, bool& isLightSource) {
        // Return tint
        isLightSource = false;
        tint = color;
        
        // Reflect
        return glm::reflect(in, norm);
    }

    void Mirror::setColor(const glm::vec3& color) {
        this->color = color;
    }
}