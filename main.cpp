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

    /**
      IMPORTANT: Models MUST be smooth shaded
     * **/

    auto* mesh = new ThreeD::Mesh();
    mesh->CastFromArray(DragonVertices, sizeof(DragonVertices) / sizeof(DragonVertices[0]));
    mesh->indices = DragonIndices;
    mesh->indicesCount = sizeof(DragonIndices) / sizeof(DragonIndices[0]);
    mesh->shader = basicShader;
    mesh->material = ThreeD::Material();
    mesh->material.diffuse = Math::Vector3(0.07568f, 0.61424f, 0.07568f);
    mesh->material.ambient = Math::Vector3(0.0215f, 0.1745f, 0.0215f);
    mesh->material.specular = Math::Vector3(0.633f, 0.727811f,0.633f);
    mesh->material.shininess =  250.f;
    mesh->name = "Dragon";
    mesh->position = {0, 0, 20};
    mesh->rotation = Math::Quaternion::Euler({0, 0, 0});
    mesh->scale = {1, 1,1};

    auto* mesh2 = new ThreeD::Mesh();
    loadObjMesh(mesh2, "./TestObjects/cube.obj", "./TestObjects/materials/");
    mesh2->shader = basicShader;
    mesh2->name = "Cube";
    mesh2->position = {4,0,10};
    mesh2->rotation = Math::Quaternion::Euler({0, 0, 0});

    auto* mesh3 = new ThreeD::Mesh();
    loadObjMesh(mesh3, "./TestObjects/cube_wood.obj", "./TestObjects/materials/");
    mesh3->shader = basicShader;
    mesh3->name = "Cube Wood";
    mesh3->position = {-4,0,10};
    mesh3->rotation = Math::Quaternion::Euler({0, 0, 0});


    auto* mesh4 = new ThreeD::Mesh();
    loadObjMesh(mesh4, "./TestObjects/borne_darcade_Pacman.obj", "./TestObjects/materials/");
    mesh4->shader = basicShader;
    mesh4->name = "Borne";

    mesh4->material = ThreeD::Material();
    mesh4->material.diffuse = Math::Vector3(1, 0.7, 0.7);
    mesh4->material.ambient = Math::Vector3(0, 0, 0);
    mesh4->material.specular = Math::Vector3(0, 0,0);
    mesh4->material.shininess =  20.f;

    mesh4->position = {0, -5, 10};
    mesh4->rotation = Math::Quaternion::Euler({0, 0, 0});


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

    int meshCount = 4;
    auto* meshes = new ThreeD::Mesh[meshCount];

    meshes[0] = *mesh;
    meshes[1] = *mesh2;
    meshes[2] = *mesh3;
    meshes[3] = *mesh4;

    std::chrono::time_point<std::chrono::system_clock> start, end;

    float deltaTime = 0;

    while (!glfwWindowShouldClose(window))
    {

        start = std::chrono::system_clock::now();

        processControls(window, camera, deltaTime);

        meshes[0].rotateAroundAnAxis({0,0,0}, Math::Quaternion::Euler(0, M_PI * deltaTime, 0));

        meshes[1].rotate(Math::Quaternion::Euler(M_PI * deltaTime, 0, 0));

        meshes[2].rotateAroundAnAxis({0,0,0},Math::Quaternion::Euler(M_PI * deltaTime, M_PI * deltaTime, M_PI * deltaTime));

        meshes[3].rotateAroundAnAxis(meshes[1].position, Math::Quaternion::Euler(0, 0,  M_PI * deltaTime));

        light.rotateAroundAnAxis({0,0,0}, Math::Quaternion::Euler(0, -M_PI * deltaTime, 0) );

        app.render(window, meshes, meshCount, camera, light);

        glfwSwapBuffers(window);
        glfwPollEvents();

        end = std::chrono::system_clock::now();
        deltaTime = (end - start).count() / 1000000000.0f;
        glfwSetWindowTitle(glfwGetCurrentContext(), (title + std::to_string(1.0f / deltaTime)).c_str());
    }

    delete mesh;
    delete mesh2;
    delete mesh3;
    delete mesh4;

    app.deinitialize(meshes, meshCount);

    glfwTerminate();
    return 0;
}