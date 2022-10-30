#include "render_target.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

namespace rt {
    RenderTarget::RenderTarget(const glm::vec<2, int>& res) {
        this->res = res;
        data = new glm::vec3[res.x*res.y];
        memset(data, 0, sizeof(glm::vec3) * res.x*res.y);
    }

    RenderTarget::~RenderTarget() {
        delete[] data;
    }

    glm::vec<2, int> RenderTarget::getResolution() {
        return res;
    }

    void RenderTarget::save(std::string path) {
        uint8_t* rgba = new uint8_t[res.x*res.y*4];
        for (int y = 0; y < res.y; y++) {
            for (int x = 0; x < res.x; x++) {
                rgba[(y *  res.x * 4) + (x * 4) + 0] = std::min<int>(data[(y * res.x) + x].r * 255.0f, 255);
                rgba[(y *  res.x * 4) + (x * 4) + 1] = std::min<int>(data[(y * res.x) + x].g * 255.0f, 255);
                rgba[(y *  res.x * 4) + (x * 4) + 2] = std::min<int>(data[(y * res.x) + x].b * 255.0f, 255);
                rgba[(y *  res.x * 4) + (x * 4) + 3] = 255;
            }
        }
        stbi_write_png(path.c_str(), res.x, res.y, 4, rgba, res.x*4);
        delete[] data;
    }
}