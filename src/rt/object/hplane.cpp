#include "hplane.h"

namespace rt::object {
    HPlane::HPlane(std::shared_ptr<Material> mat, glm::vec3 pos, glm::vec2 size) {
        this->pos = pos;
        this->size = size;
        materials.push_back(mat);
        
        update();
    }

    const std::vector<glm::vec3>& HPlane::getVertices() {
        return vertices;
    }

    const std::vector<std::shared_ptr<Material>>& HPlane::getMaterials() {
        return materials;
    }

    const std::vector<glm::vec<4, int>>& HPlane::getIndices() {
        return indices;
    }

    void HPlane::update() {
        // Clear lists
        vertices.clear();
        indices.clear();

        // Create vertices
        float dx = size.x / 2.0f;
        float dz = size.y / 2.0f;
        vertices.push_back(pos + glm::vec3(-dx, 0.0f, -dz));
        vertices.push_back(pos + glm::vec3( dx, 0.0f, -dz));
        vertices.push_back(pos + glm::vec3(-dx, 0.0f,  dz));
        vertices.push_back(pos + glm::vec3( dx, 0.0f,  dz));
        
        // Left
        indices.push_back(glm::vec<4, int>(0, 1, 2, 0));
        indices.push_back(glm::vec<4, int>(1, 2, 3, 0));
    }
}