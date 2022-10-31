#include "rt/material/lambertian.h"
#include "rt/material/light_source.h"
#include "rt/material/mirror.h"
#include "rt/material/glass.h"
#include "rt/camera.h"
#include "rt/scene.h"
#include "rt/object/cube.h"
#include "rt/object/hplane.h"
#include "rt/object/obj.h"
#include "rt/rt.h"
#include "rt/postproc.h"
#include <time.h>
#include <functional>

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

    auto _5_5kLight = std::make_shared<rt::material::LightSource>(glm::vec3(248.0f / 255.0f, 255.0f / 255.0f, 183.0f / 255.0f), 10.0f);

    auto cyanLight = std::make_shared<rt::material::LightSource>(glm::vec3(0.1f, 1.0f, 1.0f), 3.0f);
    auto magLight = std::make_shared<rt::material::LightSource>(glm::vec3(1.0f, 0.1f, 1.0f), 3.0f);
    auto yelLight = std::make_shared<rt::material::LightSource>(glm::vec3(1.0f, 1.0f, 0.1f), 3.0f);

    auto cyanMirror = std::make_shared<rt::material::Mirror>(glm::vec3(0.2f, 1.0f, 1.0f));

    auto glass = std::make_shared<rt::material::Glass>(glm::vec3(1.0f, 1.0f, 1.0f));
    
    // Create camera
    auto camera = std::make_shared<rt::Camera>(glm::vec3(0.0, 0.0, 1.6), glm::vec3(0, -sin(0.2), cos(0.2)), glm::vec3(0, cos(0.2), sin(0.2)), 72.0f);

    // Create scene
    auto scene = std::make_shared<rt::Scene>();
    auto room = std::make_shared<rt::object::Cube>(glm::vec3(0, 0, 2.5f), glm::vec3(2.0f, 2.0f, 2.0f), whiteWall, whiteWall, whiteWall, whiteWall, redWall, greenWall);

    auto cube1 = std::make_shared<rt::object::Cube>(glm::vec3(-0.7, -0.9, 3.2f), glm::vec3(0.15f, 0.15f, 0.15f), cyanLight, cyanLight, cyanLight, cyanLight, cyanLight, cyanLight);
    auto cube2 = std::make_shared<rt::object::Cube>(glm::vec3(0.0, -0.9, 3.2f), glm::vec3(0.15f, 0.15f, 0.15f), magLight, magLight, magLight, magLight, magLight, magLight);
    auto cube3 = std::make_shared<rt::object::Cube>(glm::vec3(0.7, -0.9, 3.2f), glm::vec3(0.15f, 0.15f, 0.15f), yelLight, yelLight, yelLight, yelLight, yelLight, yelLight);

    auto glassCube = std::make_shared<rt::object::Cube>(glm::vec3(-0.5, -0.5, 3.0f), glm::vec3(0.3f, 0.3f, 0.3f), cyanMirror, cyanMirror, cyanMirror, cyanMirror, cyanMirror, cyanMirror);

    auto lght = std::make_shared<rt::object::HPlane>(_5_5kLight, glm::vec3(0, 1.0f - 0.01f, 2.5f), glm::vec2(0.6f, 0.6f));
    auto obj = std::make_shared<rt::object::OBJ>("../res/sphere.obj", glm::vec3(0, -0.3, 2.5), glm::vec3(0.1, 0.1, 0.1), cyanMirror);
    scene->addObject(room);
    scene->addObject(lght);

    auto test = &rt::Camera::setFOV;
    
    //scene->addObject(cube1);
    //scene->addObject(cube2);
    //scene->addObject(cube3);
    //scene->addObject(glassCube);
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

    // Post-process
    rt::postproc::normalize(target, 1.0f / (float)sampCount);
    rt::postproc::gamma(target);

    // Save generate image
    printf("Saving...\n");
    target->save("../output/out.png");


    return 0;
}