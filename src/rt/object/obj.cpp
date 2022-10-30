#include "obj.h"
#include <fstream>

namespace rt::object {
    std::vector<std::string> split(std::string str, char c) {
        std::string part;
        std::vector<std::string> parts;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == c) {
                parts.push_back(part);
                part = "";
                continue;
            }
            part += str[i];
        }
        parts.push_back(part);
        return parts;
    }

    OBJ::OBJ(std::string path, glm::vec3 pos, glm::vec3 scale, std::shared_ptr<Material> mat) {
        this->pos = pos;
        this->scale = scale;
        materials.push_back(mat);

        std::ifstream file(path);
        for( std::string line; std::getline(file, line); ) {
            
            std::vector<std::string> parts = split(line, ' ');
            if (parts[0] == "v") {
                vertices.push_back(glm::vec3(std::stof(parts[1]) * scale.x, std::stof(parts[2]) * scale.y, std::stof(parts[3]) * scale.z) + pos);
            }
            else if (parts[0] == "f") {
                int id1 = std::stoi(split(parts[1], '/')[0]) - 1;
                int id2 = std::stoi(split(parts[2], '/')[0]) - 1;
                int id3 = std::stoi(split(parts[3], '/')[0]) - 1;
                indices.push_back(glm::vec<4, int>(id1, id2, id3, 0));
            }
        }

        printf("Loaded %d vertices and %d indices.\n", vertices.size(), indices.size());
    }

    const std::vector<glm::vec3>& OBJ::getVertices() {
        return vertices;
    }

    const std::vector<std::shared_ptr<Material>>& OBJ::getMaterials() {
        return materials;
    }

    const std::vector<glm::vec<4, int>>& OBJ::getIndices() {
        return indices;
    }
}