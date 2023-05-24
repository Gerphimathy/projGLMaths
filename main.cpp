#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <ostream>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <list>

#include "ThreeD/Mesh.hpp"
#include "ThreeD/Material.hpp"
#include "TestObjects/DragonData.h"

#include "loader/loadMesh.h"

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

#include "window/Application.hpp"
#include "ThreeD/Camera.h"

int main(void) {
    Window::Application app;
    GLFWwindow* window;
    auto* meshes = new ThreeD::Mesh[3];

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "Projet OpenGL & Maths", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    app.initialize();

    auto* basicShader = new GLShader();
    basicShader->LoadVertexShader(
            "../shaders/basic/basic.vs.glsl"
    );
    basicShader->LoadFragmentShader(
            "../shaders/basic/basic.fs.glsl"
    );
    basicShader->Create();

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
    mesh->position = {0, 0, -20};

    meshes[0] = *mesh;

    auto* mesh2 = new ThreeD::Mesh();
    loadObjMesh(mesh2, "../TestObjects/cube.obj", "../TestObjects/materials/");
    mesh2->shader = basicShader;
    mesh2->name = "Cube";

    meshes[1] = *mesh2;

    auto* mesh3 = new ThreeD::Mesh();
    loadObjMesh(mesh3, "../TestObjects/ube_wood.obj", "../TestObjects/materials/");
    mesh3->shader = basicShader;
    mesh3->name = "Cube Wood";
    mesh3->position = {0,0,-20};

    meshes[2] = *mesh3;

    Camera camera = Camera();


    while (!glfwWindowShouldClose(window))
    {
        camera.rotation *= Math::Quaternion::Euler({0.1,0,0});
        //std::cout << camera.rotation.ToMatrix() << std::endl;
        app.render(window, meshes, 2, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app.deinitialize(meshes, 2);

    glfwTerminate();
    return 0;
}