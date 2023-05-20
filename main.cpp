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
    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    app.initialize();

    ThreeD::Mesh testCube;
    testCube.vertices = new ThreeD::Vertex[8];

    testCube.vertices[0].position = { -1, -1, -1 };
    testCube.vertices[0].color = { 0.5, 0.5, 0.5};

    testCube.vertices[1].position = { -1, 1, -1 };
    testCube.vertices[1].color = { 0, 1, 0};

    testCube.vertices[2].position = { 1, 1, -1 };
    testCube.vertices[2].color = { 1, 1, 0};

    testCube.vertices[3].position = { 1, -1, -1 };
    testCube.vertices[3].color = { 1, 0, 0};

    testCube.vertices[4].position = { 1, -1, 1 };
    testCube.vertices[4].color = { 1, 0, 1};

    testCube.vertices[5].position = { 1, 1, 1 };
    testCube.vertices[5].color = { 1, 1, 1};

    testCube.vertices[6].position = { -1, 1, 1 };
    testCube.vertices[6].color = { 0, 1, 1};

    testCube.vertices[7].position = { -1, -1, 1 };
    testCube.vertices[7].color = { 0, 0, 1};

    testCube.vertexCount = 8;

    meshes[0] = testCube;

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        app.setSize(width, height);

        app.render(meshes, 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app.deinitialize();

    glfwTerminate();
    return 0;
}