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

#include "tinyObjLoader/loadMesh.h"

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

int main() {
    Window::Application app;
    GLFWwindow* window;
    auto* meshes = new ThreeD::Mesh[2];

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

    auto* mesh = new ThreeD::Mesh();
    mesh->CastFromArray(DragonVertices, sizeof(DragonVertices) / sizeof(DragonVertices[0]));
    mesh->indices = DragonIndices;
    mesh->indicesCount = sizeof(DragonIndices) / sizeof(DragonIndices[0]);
    mesh->shader = basicShader;
    mesh->material = ThreeD::Material();
    mesh->material.diffuse = Math::Vector3(0.07568f, 0.61424f, 0.07568f);
    mesh->material.ambient = Math::Vector3(0.0215f, 0.1745f, 0.0215f);
    mesh->material.specular = Math::Vector3(0.633f, 0.727811f,0.633f);
    mesh->material.shininess =  76.8f;
    mesh->name = "Dragon";

    meshes[0] = *mesh;

    auto* mesh2 = new ThreeD::Mesh();
    loadMesh(mesh2, "../TestObjects/cube.obj", "../TestObjects/materials/");
    mesh2->shader = basicShader;
    mesh2->name = "Cube";

    meshes[1] = *mesh2;

    while (!glfwWindowShouldClose(window))
    {
        app.render(window, meshes, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app.deinitialize(meshes, 2);

    glfwTerminate();
    return 0;
}