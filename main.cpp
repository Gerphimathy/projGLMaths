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
#include "DragonData.h"

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

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyObjLoader/tiny_obj_loader.h"

#include "window/Application.hpp"

int main() {
    Window::Application app;
    GLFWwindow* window;
    auto* meshes = new ThreeD::Mesh[1];

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

    auto* mesh = new ThreeD::Mesh();
    mesh->CastFromArray(DragonVertices, sizeof(DragonVertices) / sizeof(DragonVertices[0]));
    mesh->indices = DragonIndices;
    mesh->indicesCount = sizeof(DragonIndices) / sizeof(DragonIndices[0]);

    meshes[0] = *mesh;

    while (!glfwWindowShouldClose(window))
    {
        app.render(window, meshes, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app.deinitialize();

    glfwTerminate();
    return 0;
}