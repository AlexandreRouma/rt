#pragma once
#include "scene.h"
#include "camera.h"
#include "render_target.h"

namespace rt {
    void trace(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> cam, std::shared_ptr<RenderTarget> target, int maxBounces = 10);
}