#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <ostream>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <list>
#include <chrono>
#include <map>

#include "ThreeD/Mesh.hpp"
#include "ThreeD/Material.hpp"
#include "TestObjects/DragonData.h"

#include "loader/loadMesh.h"
#include "TestObjects/DefaultMaterials.h"

#include "window/Application.hpp"
#include "window/Controls.hpp"


#include "ThreeD/Camera.h"
#include "ThreeD/Light.h"

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif


extern "C"
{
    DLLEXPORT unsigned long NvOptimusEnablement = 0x00000001;
    DLLEXPORT int AmdPowerXpressRequestHighPerformance = 1;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyCodes[key] = true; // Handle key press
    }
    if (action == GLFW_RELEASE) {
        keyCodes[key] = false; // Handle key release
    }
}


// During init, enable debug output

int main(void) {
    const std::string title = "Projet OpenGL & Maths - ";

    Window::Application app;
    GLFWwindow* window;


    if (!glfwInit()) return -1;

    window = glfwCreateWindow(1080, 720, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);

    //TODO: Trouver le bon intervasdlle pour que ça booste bien
    //glfwSwapInterval(1);
    app.initialize();

    auto* basicShader = new GLShader();
    basicShader->LoadVertexShader(
            "./shaders/basic/basic.vs.glsl"
    );
    basicShader->LoadFragmentShader(
            "./shaders/basic/basic.fs.glsl"
    );
    basicShader->Create();

    bool verbose = true;
    auto defMats = defaultMaterials();

    auto* structure = new ThreeD::Mesh();
    loadObjMesh(structure, "./TestObjects/structure-boite-de-nuit.obj", "./TestObjects/materials/", verbose);
    structure->shader = basicShader;
    structure->name = "Structure";
    structure->position = {0, 1, 0};

    auto* props = new ThreeD::Mesh();
    loadObjMesh(props, "./TestObjects/props-boite-de-nuit.obj", "./TestObjects/materials/", verbose);
    props->shader = basicShader;
    props->name = "Props";
    props->position = {0, 1, 0};

    auto* ball = new ThreeD::Mesh();
    loadObjMesh(ball, "./TestObjects/boule-boite-de-nuit.obj", "./TestObjects/materials/", verbose);
    ball->shader = basicShader;
    ball->name = "Boule";
    ball->position = {0, 1, 0};


    int dragonVerticesCount = sizeof(DragonVertices) / sizeof(float);
    int dragonIndicesCount = sizeof(DragonIndices) / sizeof(uint16_t);

    auto* goldDragon = new ThreeD::Mesh();
    goldDragon->CastFromArray(DragonVertices, DragonIndices, dragonVerticesCount, dragonIndicesCount);
    goldDragon->shader = basicShader;
    goldDragon->name = "Dragon Porte Entrée Gauche";
    goldDragon->position = {0,1,0};
    goldDragon->materials = new ThreeD::Material[1];
    goldDragon->materials[0] = *defMats["Gold"];
    goldDragon->materialCount = 1;

    auto* silverDragon = new ThreeD::Mesh();
    silverDragon->CastFromArray(DragonVertices, DragonIndices, dragonVerticesCount, dragonIndicesCount);
    silverDragon->shader = basicShader;
    silverDragon->name = "Dragon  Porte Entrée Droite";
    silverDragon->position = {0,1,30};
    silverDragon->materials = new ThreeD::Material[1];
    silverDragon->materials[0] = *defMats["Silver"];
    silverDragon->materialCount = 1;

    auto* ebonyDragon = new ThreeD::Mesh();
    ebonyDragon->CastFromArray(DragonVertices, DragonIndices, dragonVerticesCount, dragonIndicesCount);
    ebonyDragon->shader = basicShader;
    ebonyDragon->name = "Dragon Central";
    ebonyDragon->position = {281,-9.5f,15};
    ebonyDragon->scale = {1.5f, 1.5f, 1.5f};
    ebonyDragon->materials = new ThreeD::Material[1];
    ebonyDragon->materials[0] = *defMats["Ebony"];
    ebonyDragon->materialCount = 1;

    int meshCount = 6;
    auto* meshes = new ThreeD::Mesh[meshCount];
    meshes[0] = *structure;
    meshes[1] = *goldDragon;
    meshes[2] = *silverDragon;
    meshes[3] = *ebonyDragon;
    meshes[4] = *ball;

    meshes[5] = *props;

    ThreeD::Camera camera = ThreeD::Camera();

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    const float aspectRatio = float(width)/float(height);
    const float zNear = 0.1f, zFar = 1000.0f;
    const float fovy = 45.f * M_PI/180.f;
    const float cot = 1.f / tanf(fovy / 2.f);
    camera.projectionMatrix = std::array<float, 16>({
            cot/aspectRatio, 0.f, 0.f, 0.f, // 1ere colonne
            0.f, cot, 0.f, 0.f,
            0.f, 0.f, -zFar/(zFar-zNear), -1.f,
            0.f, 0.f, -zFar*zNear/(zFar-zNear), 0.f
    });
    camera.rotation = Math::Quaternion::Euler(0, M_PI, 0);

    ThreeD::Light light = ThreeD::Light();
    light.position = Math::Vector3(281.0f, 21.f, 15.0f);

    light.ambient = Math::Vector3(1.0f, 1.0f, 1.0f);
    light.diffuse = Math::Vector3(1.0f, 1.0f, 1.0f);
    light.specular = Math::Vector3(1.0f, 1.0f, 1.0f);
    light.color = Math::Vector3(1.0f, 1.0f, 1.0f);

    std::chrono::time_point<std::chrono::system_clock> start, end;

    float deltaTime = 0;

    while (!glfwWindowShouldClose(window))
    {
        start = std::chrono::system_clock::now();

        processControls(window, camera, deltaTime);

        app.render(window, meshes, meshCount, camera, light, false);

        meshes[3].rotateAroundAnAxis(meshes[3].position, Math::Quaternion::Euler(0, M_PI*deltaTime, 0));

        glfwSwapBuffers(window);
        glfwPollEvents();

        end = std::chrono::system_clock::now();
        deltaTime = (end - start).count() / 1000000000.0f;
        glfwSetWindowTitle(glfwGetCurrentContext(), (title + std::to_string(1.0f / deltaTime)).c_str());
    }

    app.deinitialize(meshes, meshCount);

    delete[] meshes;
    delete basicShader;

    for (auto& mat : defMats) {
        delete mat.second;
    }

    glfwTerminate();
    return 0;
}