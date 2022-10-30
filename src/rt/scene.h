#pragma once
#include <memory>
#include <vector>
#include "ray.h"
#include "material.h"
#include "object.h"

namespace rt {
    class Scene {
    public:
        bool probe(const Ray& ray, std::shared_ptr<Material>& mat, float& distance, glm::vec3& norm, glm::vec2& texcoord);

        void addObject(std::shared_ptr<Object> object);

        void build();

        std::vector<glm::vec<4, int>> indices;
        std::vector<glm::vec3> vertices;
        std::vector<std::shared_ptr<Material>> materials;

    private:
        std::vector<std::shared_ptr<Object>> objects;

    };
}