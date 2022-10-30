#pragma once
#include "../glm/glm.hpp"
#include <memory>
#include <string>

namespace rt {
    class RenderTarget {
    public:
        RenderTarget(const glm::vec<2, int>& res);
        ~RenderTarget();

        glm::vec<2, int> getResolution();

        void save(std::string path);

    //private:
        glm::vec<2, int> res;
        glm::vec3* data;
    };
}