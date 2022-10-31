#pragma once
#include "render_target.h"

namespace rt::postproc {
    void normalize(std::shared_ptr<RenderTarget>& target, float factor);
    void gamma(std::shared_ptr<RenderTarget>& target, float gamma = 2.2);
}