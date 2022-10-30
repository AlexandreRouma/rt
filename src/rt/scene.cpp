#include "scene.h"
#include "../glm/gtx/intersect.hpp"
#include "../glm/gtx/normal.hpp"

namespace rt {
    bool Scene::probe(const Ray& ray, std::shared_ptr<Material>& mat, float& distance, glm::vec3& norm, glm::vec2& texcoord) {
        int bestIdx = -1;
        glm::vec2 coords;
        glm::vec2 bestTexcoord;
        float bestDist = INFINITY;
        float dist;
        for (int i = 0; i < indices.size(); i++) {
            auto ind = indices[i];

            // Check if the ray intersects
            const glm::vec3& a = vertices[ind.x];
            const glm::vec3& b = vertices[ind.y];
            const glm::vec3& c = vertices[ind.z];
            if (!glm::intersectRayTriangle(ray.org, ray.dir, a, b, c, coords, dist)) { continue; }

            // Check if closer and non negative
            if (dist > bestDist || dist < 0.0f) { continue; }

            // Keep as best
            bestIdx = i;
            bestDist = dist;
            bestTexcoord = coords;
        }

        // If no hit, return
        if (bestIdx < 0) { return false; }

        // Set hit parameters
        distance = bestDist;
        texcoord = bestTexcoord;

        // Compute normal
        auto ind = indices[bestIdx];
        const glm::vec3& a = vertices[ind.x];
        const glm::vec3& b = vertices[ind.y];
        const glm::vec3& c = vertices[ind.z];
        norm = glm::triangleNormal(a, b, c);
        if (glm::dot(norm, ray.dir) > 0.0f) { norm *= -1.0f; }
        mat = materials[ind.w];

        return true;
    }

    void Scene::addObject(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    void Scene::build() {
        vertices.clear();
        indices.clear();
        materials.clear();

        for (auto& obj : objects) {
            glm::vec<4, int> indCorr(vertices.size(), vertices.size(), vertices.size(), materials.size());
            for (auto& vert : obj->getVertices()) { vertices.push_back(vert); }
            for (auto& mat : obj->getMaterials()) { materials.push_back(mat); }
            for (auto& ind : obj->getIndices()) { indices.push_back(ind + indCorr); }
        }
    }
}