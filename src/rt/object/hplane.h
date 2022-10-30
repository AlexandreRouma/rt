#pragma once
#include <memory>
#include "../object.h"
#include "../material.h"

namespace rt::object {
    class HPlane : public Object {
    public:
        HPlane(std::shared_ptr<Material> mat, glm::vec3 pos, glm::vec2 size);

        const std::vector<glm::vec3>& getVertices();
        const std::vector<std::shared_ptr<Material>>& getMaterials();
        const std::vector<glm::vec<4, int>>& getIndices();

    private:
        void update();

        std::vector<glm::vec3> vertices;
        std::vector<std::shared_ptr<Material>> materials;
        std::vector<glm::vec<4, int>> indices;

        glm::vec3 pos;
        glm::vec2 size;

    };
}