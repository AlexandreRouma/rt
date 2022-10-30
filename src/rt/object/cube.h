#pragma once
#include <memory>
#include "../object.h"
#include "../material.h"

namespace rt::object {
    class Cube : public Object {
    public:
        Cube(glm::vec3 pos, glm::vec3 size, std::shared_ptr<Material> frMat, std::shared_ptr<Material> bkMat, std::shared_ptr<Material> tpMat, std::shared_ptr<Material> btMat, std::shared_ptr<Material> lfMat, std::shared_ptr<Material> rgMat);

        const std::vector<glm::vec3>& getVertices();
        const std::vector<std::shared_ptr<Material>>& getMaterials();
        const std::vector<glm::vec<4, int>>& getIndices();

    private:
        void update();

        std::vector<glm::vec3> vertices;
        std::vector<std::shared_ptr<Material>> materials;
        std::vector<glm::vec<4, int>> indices;

        glm::vec3 pos;
        glm::vec3 size;
        std::shared_ptr<Material> frMat;
        std::shared_ptr<Material> bkMat;
        std::shared_ptr<Material> tpMat;
        std::shared_ptr<Material> btMat;
        std::shared_ptr<Material> lfMat;
        std::shared_ptr<Material> rgMat;
    };
}