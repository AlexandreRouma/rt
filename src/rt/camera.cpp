#include "camera.h"
#include <glm/gtc/random.hpp>

namespace rt {
    RayField::RayField(glm::vec<2, int> res) {
        this->res = res;
        field = new Ray[res.x * res.y];
    }

    RayField::~RayField() {
        delete[] field;
    }

    const Ray& RayField::get(const glm::vec<2, int>& pos) {
        return field[(pos.y * res.x) + pos.x];
    }

    glm::vec<2, int> RayField::getResolution() {
        return res;
    }

    Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float fov) {
        this->position = position;
        this->front = front;
        this->up = up;
        this->fov = fov;
        side = glm::cross(up, front);
    }

    void Camera::setPosition(glm::vec3 position) {
        this->position = position;
    }

    void Camera::setOrientation(glm::vec3 front, glm::vec3 up) {
        this->front = front;
        this->up = up;
        side = glm::cross(up, front);
    }

    void Camera::setFOV(float fov) {
        this->fov = fov;
    }

    std::shared_ptr<RayField> Camera::genRayField(glm::vec<2, int> res, bool dither) {
        std::shared_ptr<RayField> rf = std::make_shared<RayField>(res);
        Ray* field = rf->field;

        float dx = 1.0f / (float)res.x;
        float ox = dx * (float)(res.x - 1) / 2.0f;
        float oy = dx * (float)(res.y - 1) / 2.0f;
        float d = 0.5 / tanf(fov*(3.14159265359/180.0)/2.0f);

        Ray r;
        r.org = position;
        for (int y = 0; y < res.y; y++) {
            for (int x = 0; x < res.x; x++) {
                float fx = (x * dx) - ox;
                float fy = (y * dx) - oy;
                if (dither) {
                    fx += glm::linearRand(-0.5, 0.5) * dx;
                    fy += glm::linearRand(-0.5, 0.5) * dx;
                }
                r.dir = glm::normalize(fx*side - fy*up + d*front);
                field[(y * res.x) + x] = r;
            }
        }

        return rf;
    }
}