#include "cube.h"

namespace rt::object {
    Cube::Cube(glm::vec3 pos, glm::vec3 size, std::shared_ptr<Material> frMat, std::shared_ptr<Material> bkMat, std::shared_ptr<Material> tpMat, std::shared_ptr<Material> btMat, std::shared_ptr<Material> lfMat, std::shared_ptr<Material> rgMat) {
        this->pos = pos;
        this->size = size;
        this->bkMat = bkMat;
        this->frMat = frMat;
        this->tpMat = tpMat;
        this->btMat = btMat;
        this->lfMat = lfMat;
        this->rgMat = rgMat;

        update();
    }

    const std::vector<glm::vec3>& Cube::getVertices() {
        return vertices;
    }

    const std::vector<std::shared_ptr<Material>>& Cube::getMaterials() {
        return materials;
    }

    const std::vector<glm::vec<4, int>>& Cube::getIndices() {
        return indices;
    }

    void Cube::update() {
        // Clear lists
        vertices.clear();
        materials.clear();
        indices.clear();

        // Create vertices
        float dx = size.x / 2.0f;
        float dy = size.y / 2.0f;
        float dz = size.z / 2.0f;
        vertices.push_back(pos + glm::vec3(-dx,  dy, -dz));
        vertices.push_back(pos + glm::vec3( dx,  dy, -dz));
        vertices.push_back(pos + glm::vec3(-dx, -dy, -dz));
        vertices.push_back(pos + glm::vec3( dx, -dy, -dz));
        vertices.push_back(pos + glm::vec3(-dx,  dy,  dz));
        vertices.push_back(pos + glm::vec3( dx,  dy,  dz));
        vertices.push_back(pos + glm::vec3(-dx, -dy,  dz));
        vertices.push_back(pos + glm::vec3( dx, -dy,  dz));

        // Create materials
        materials.push_back(lfMat);
        materials.push_back(rgMat);
        materials.push_back(tpMat);
        materials.push_back(btMat);
        materials.push_back(frMat);
        materials.push_back(bkMat);
        
        // Indices
        indices.push_back(glm::vec<4, int>(0, 4, 2, 0));
        indices.push_back(glm::vec<4, int>(4, 2, 6, 0));
        indices.push_back(glm::vec<4, int>(1, 3, 7, 1));
        indices.push_back(glm::vec<4, int>(1, 7, 5, 1));
        indices.push_back(glm::vec<4, int>(4, 1, 5, 2));
        indices.push_back(glm::vec<4, int>(0, 4, 1, 2));
        indices.push_back(glm::vec<4, int>(6, 2, 7, 3));
        indices.push_back(glm::vec<4, int>(3, 7, 2, 3));
        indices.push_back(glm::vec<4, int>(0, 1, 2, 4));
        indices.push_back(glm::vec<4, int>(1, 2, 3, 4));
        indices.push_back(glm::vec<4, int>(4, 5, 6, 5));
        indices.push_back(glm::vec<4, int>(5, 6, 7, 5));
        indices.push_back(glm::vec<4, int>(8, 9, 10, 6));
        indices.push_back(glm::vec<4, int>(9, 10, 11, 6));
    }
}