#pragma once
#include <memory>
#include <string>
#include "../object.h"
#include "../material.h"

namespace rt::object {
    class OBJ : public Object {
    public:
        OBJ(std::string path, glm::vec3 pos, glm::vec3 scale, std::shared_ptr<Material> mat);

        const std::vector<glm::vec3>& getVertices();
        const std::vector<std::shared_ptr<Material>>& getMaterials();
        const std::vector<glm::vec<4, int>>& getIndices();

    private:
        void update();

        std::vector<glm::vec3> vertices;
        std::vector<std::shared_ptr<Material>> materials;
        std::vector<glm::vec<4, int>> indices;

        glm::vec3 pos;
        glm::vec3 scale;

    };
}