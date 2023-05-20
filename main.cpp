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
    app.initialize();

    ThreeD::Mesh testMesh;
    testMesh.polygonCount = 2;
    testMesh.polygons = new ThreeD::Polygon[2];

    ThreeD::Polygon bigTriangle;
    ThreeD::Polygon smallTriangle;

    bigTriangle.vertexCount = 3;
    bigTriangle.vertices = new ThreeD::Vertex[3];
    bigTriangle.vertices[0] = ThreeD::Vertex(Math::Vector3(-0.8f, -0.8f, -1.f), Math::Vector3(1.f, 0.f, 0.f));
    bigTriangle.vertices[1] = ThreeD::Vertex(Math::Vector3(0.8f, -0.8f, -1.f), Math::Vector3(0.f, 1.f, 0.f));
    bigTriangle.vertices[2] = ThreeD::Vertex(Math::Vector3(0.f, 0.8f, -1.f), Math::Vector3(0.f, 0.f, 1.f));


    smallTriangle.vertexCount = 3;
    smallTriangle.vertices = new ThreeD::Vertex[3];
    smallTriangle.vertices[0] = ThreeD::Vertex(Math::Vector3(-0.5f, -0.5f, 1.0f), Math::Vector3(0.f, 0.f, 1.f));
    smallTriangle.vertices[1] = ThreeD::Vertex(Math::Vector3(0.5f, -0.5f, 1.0f), Math::Vector3(0.f, 1.f, 0.f));
    smallTriangle.vertices[2] = ThreeD::Vertex(Math::Vector3(0.f, 0.5f, 1.0f), Math::Vector3(1.f, 0.f, 0.f));

    testMesh.polygons[1] = bigTriangle;
    testMesh.polygons[0] = smallTriangle;

    meshes[0] = testMesh;

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