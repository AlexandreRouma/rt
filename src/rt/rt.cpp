#include "rt.h"

#define EPSILON     0.000001f

namespace rt {
    void trace(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> cam, std::shared_ptr<RenderTarget> target, int maxBounces) {
        // Generate ray field
        auto res = target->getResolution();
        auto rf = cam->genRayField(res, true);

        // Iterate over entire rayfield
        #pragma omp parallel for schedule(dynamic)
        for (int y = 0; y < res.y; y++) {
            std::shared_ptr<rt::Material> mat;
            float distance;
            glm::vec3 norm;
            glm::vec2 texcoord;
            glm::vec3 tint;
            for (int x = 0; x < res.x; x++) {
                // Get camera ray
                Ray ray = rf->get(glm::vec<2, int>(x, y));

                // Iteratively bounce the ray
                glm::vec3 albedo(1.0f, 1.0f, 1.0f);
                bool source = false;
                for (int i = 0; i < maxBounces; i++) {
                    // If no contact, give u^p
                    if (!scene->probe(ray, mat, distance, norm, texcoord)) {
                        break;
                    }

                    // Move ray origin and interact with the material. If light source, return
                    // TODO: tint must be modulated by angle of attack glm::dot(norm, dir)
                    ray.org += ray.dir * distance;
                    ray.dir = mat->interact(norm, ray.dir, tint, source);
                    ray.org += ray.dir * EPSILON;
                    albedo *= tint;
                    if (source) {
                        break;
                    }
                }
                
                // If a light wasn't hit give up
                if (!source) { continue; }

                // Add up albedo
                target->data[(y*res.x) + x] += albedo;
            }
        }
    }
}