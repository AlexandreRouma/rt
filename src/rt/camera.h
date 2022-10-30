#pragma once
#include "ray.h"
#include <memory>

namespace rt {
    class Camera;

    class RayField {
    public:
        RayField(glm::vec<2, int> res);
        ~RayField();

        const Ray& get(const glm::vec<2, int>& pos);
        glm::vec<2, int> getResolution();

        friend Camera;

    private:
        Ray* field;
        glm::vec<2, int> res;
    };

    class Camera {
    public:
        Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov);

        void setPosition(glm::vec3 position);
        void setOrientation(glm::vec3 front, glm::vec3 up);
        void setFOV(float fov);

        std::shared_ptr<RayField> genRayField(glm::vec<2, int> res, bool dither = false);

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 side;
        float fov;
    };
}