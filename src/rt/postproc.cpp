#include "postproc.h"

namespace rt::postproc {
    void normalize(std::shared_ptr<RenderTarget>& target, float factor) {
        for (int y = 0; y < target->res.y; y++) {
            for (int x = 0; x < target->res.x; x++) {
                target->data[(y*target->res.x)+x] *= factor;
            }
        }
    }

    void gamma(std::shared_ptr<RenderTarget>& target, float gamma) {
        for (int y = 0; y < target->res.y; y++) {
            for (int x = 0; x < target->res.x; x++) {
                target->data[(y*target->res.x)+x] = glm::pow(target->data[(y*target->res.x)+x], glm::vec3(1.0f / gamma, 1.0f / gamma, 1.0f / gamma));
            }
        }
    }
}