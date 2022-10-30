#include "rt/material/lambertian.h"
#include "rt/material/light_source.h"
#include "rt/material/mirror.h"
#include "rt/camera.h"
#include "rt/scene.h"
#include "rt/object/cube.h"
#include "rt/object/hplane.h"
#include "rt/object/obj.h"
#include "rt/rt.h"
#include <time.h>

int main() {
    // Seed the RNG
    srand(time(0));

    // Create materials
    auto whiteWall = std::make_shared<rt::material::Lambertian>(glm::vec3(1.0f, 1.0f, 1.0f));
    auto redWall = std::make_shared<rt::material::Lambertian>(glm::vec3(1.0f, 0.3f, 0.1f));
    auto greenWall = std::make_shared<rt::material::Lambertian>(glm::vec3(0.3f, 1.0f, 0.3f));
    auto backroomWall = std::make_shared<rt::material::Lambertian>(glm::vec3(0.78f, 0.78f, 0.32f));
    auto greyWall = std::make_shared<rt::material::Lambertian>(glm::vec3(0.3f, 0.3f, 0.3f));
    auto light = std::make_shared<rt::material::LightSource>(glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);

    auto cyanLight = std::make_shared<rt::material::LightSource>(glm::vec3(0.1f, 1.0f, 1.0f), 3.0f);
    auto magLight = std::make_shared<rt::material::LightSource>(glm::vec3(1.0f, 0.1f, 1.0f), 3.0f);
    auto yelLight = std::make_shared<rt::material::LightSource>(glm::vec3(1.0f, 1.0f, 0.1f), 3.0f);

    auto cyanMirror = std::make_shared<rt::material::Mirror>(glm::vec3(0.2f, 1.0f, 1.0f));
    
    // Create camera
    auto camera = std::make_shared<rt::Camera>(glm::vec3(0.0, 0.0, 1.6), glm::vec3(0, -sin(0.2), cos(0.2)), glm::vec3(0, cos(0.2), sin(0.2)), 72.0f);

    // Create scene
    auto scene = std::make_shared<rt::Scene>();
    auto room = std::make_shared<rt::object::Cube>(glm::vec3(0, 0, 2.5f), glm::vec3(2.0f, 2.0f, 2.0f), greyWall, greyWall, greyWall, greyWall, redWall, greenWall);

    auto cube1 = std::make_shared<rt::object::Cube>(glm::vec3(-0.7, -0.9, 3.2f), glm::vec3(0.15f, 0.15f, 0.15f), cyanLight, cyanLight, cyanLight, cyanLight, cyanLight, cyanLight);
    auto cube2 = std::make_shared<rt::object::Cube>(glm::vec3(0.0, -0.9, 3.2f), glm::vec3(0.15f, 0.15f, 0.15f), magLight, magLight, magLight, magLight, magLight, magLight);
    auto cube3 = std::make_shared<rt::object::Cube>(glm::vec3(0.7, -0.9, 3.2f), glm::vec3(0.15f, 0.15f, 0.15f), yelLight, yelLight, yelLight, yelLight, yelLight, yelLight);

    auto lght = std::make_shared<rt::object::HPlane>(light, glm::vec3(0, 1.0f - 0.01f, 2.5f), glm::vec2(0.6f, 0.6f));
    auto obj = std::make_shared<rt::object::OBJ>("../res/sphere.obj", glm::vec3(0, -0.3, 2.5), glm::vec3(0.1, 0.1, 0.1), cyanMirror);
    scene->addObject(room);
    scene->addObject(lght);
    
    //scene->addObject(cube1);
    //scene->addObject(cube2);
    //scene->addObject(cube3);

    scene->addObject(obj);
    scene->build();

    // Create render target
    auto target = std::make_shared<rt::RenderTarget>(glm::vec<2, int>(800, 800));

    // Trace
    printf("Tracing...\n");
    int sampCount = 1000;
    for (int i = 0; i < sampCount; i++) {
        printf("Sample %d\n", i);
        rt::trace(scene, camera, target);
    }

    // Normalize
    printf("Normalizing...\n");
    float norm = 1.0f / (float)sampCount;
    for (int y = 0; y < target->res.y; y++) {
        for (int x = 0; x < target->res.x; x++) {
            target->data[(y*target->res.x)+x] *= norm;
        }
    }
    
    // Apply gamma
    printf("Gamma correction...\n");
    float gamma = 2.2f;
    for (int y = 0; y < target->res.y; y++) {
        for (int x = 0; x < target->res.x; x++) {
            target->data[(y*target->res.x)+x] = glm::pow(target->data[(y*target->res.x)+x], glm::vec3(1.0f / gamma, 1.0f / gamma, 1.0f / gamma));
        }
    }

    // Save generate image
    printf("Saving...\n");
    target->save("../output/out.png");

    return 0;
}