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

#include "ThreeD/Mesh.hpp"
#include "ThreeD/Material.hpp"
#include "TestObjects/DragonData.h"
#include "TestObjects/DefaultMaterials.h"

#include "loader/loadMesh.h"

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
    glfwSwapInterval(1);
    app.initialize();

    auto* basicShader = new GLShader();
    basicShader->LoadVertexShader(
            "./shaders/basic/basic.vs.glsl"
    );
    basicShader->LoadFragmentShader(
            "./shaders/basic/basic.fs.glsl"
    );
    basicShader->Create();

    //return 0;


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
    light.position = Math::Vector3(0.0f, 20.f, 20.0f);

    light.ambient = Math::Vector3(1.0f, 1.0f, 1.0f);
    light.diffuse = Math::Vector3(1.0f, 1.0f, 1.0f);
    light.specular = Math::Vector3(1.0f, 1.0f, 1.0f);
    light.color = Math::Vector3(1.0f, 1.0f, 1.0f);

    auto defaultsMats = defaultMaterials();
    int meshCount = 4;
    auto* meshes = new ThreeD::Mesh[meshCount];

    loadObjMesh(&meshes[0], "./TestObjects/structure-boite-de-nuit.obj", "./TestObjects/materials/");
    meshes[0].shader = basicShader;
    loadObjMesh(&meshes[1], "./TestObjects/props-boite-de-nuit.obj", "./TestObjects/materials/");
    meshes[1].shader = basicShader;
    loadObjMesh(&meshes[2], "./TestObjects/boule-boite-de-nuit.obj", "./TestObjects/materials/");
    meshes[2].shader = basicShader;

    meshes[3].CastFromArray(DragonVertices, (sizeof DragonVertices) / (sizeof DragonVertices[0]));
    meshes[3].indices = DragonIndices;
    meshes[3].indicesCount = (sizeof DragonIndices) / (sizeof DragonIndices[0]);
    meshes[3].shader = basicShader;
    meshes[3].name = "Dragon 1";
    //Default materials is std::map<std::string, ThreeD::Material*>
    meshes[3].material = *defaultsMats["Jade"];

    std::chrono::time_point<std::chrono::system_clock> start, end;

    float deltaTime = 0;

    while (!glfwWindowShouldClose(window))
    {

        start = std::chrono::system_clock::now();

        processControls(window, camera, deltaTime);

        light.rotateAroundAnAxis({0,0,0}, Math::Quaternion::Euler(0, -M_PI * deltaTime, 0) );

        app.render(window, meshes, meshCount, camera, light);

        glfwSwapBuffers(window);
        glfwPollEvents();

        end = std::chrono::system_clock::now();
        deltaTime = (end - start).count() / 1000000000.0f;
        glfwSetWindowTitle(glfwGetCurrentContext(), (title + std::to_string(1.0f / deltaTime)).c_str());
    }

    app.deinitialize(meshes, meshCount);
    delete[] meshes;

    glfwTerminate();
    return 0;
}