#include "lambertian.h"
#include <glm/gtc/random.hpp>

#define M_PI            3.14159265358979323846
#define M_2_PI          2.0 * M_PI

namespace rt::material {
    Lambertian::Lambertian(const glm::vec3& color) {
        this->color = color;
    }

    glm::vec3 Lambertian::interact(const glm::vec3& norm, const glm::vec3& in, glm::vec3& tint, float& refractIdx, bool& isLightSource) {
        // Return tint
        isLightSource = false;
        
        // Do lambertial BRDF
        glm::vec3 uu = glm::normalize(glm::cross(norm, { 0.0f, 1.0f, 1.0f }));
        glm::vec3 vv = glm::cross(uu, norm);
        float r0 = glm::linearRand(0.0f, 1.0f);
        float r1 = glm::linearRand(0.0f, 1.0f);
        float ra = sqrtf(r1);
        float rx = ra * cosf(M_2_PI * r0);
        float ry = ra * sinf(M_2_PI * r0);
        float rz = sqrtf(1.0f - r1);
        glm::vec3 out = glm::normalize(rx * uu + ry * vv + rz * norm);

        tint = color * fabsf(glm::dot(out, norm));

        return out;
    }

    void Lambertian::setColor(const glm::vec3& color) {
        this->color = color;
    }
}