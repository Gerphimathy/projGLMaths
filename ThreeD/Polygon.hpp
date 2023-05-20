#pragma once

#include "Vertex.hpp"
#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include "../shaders/GLShader.hpp"

namespace ThreeD {
    class Vertex;

    struct Polygon {
        ThreeD::Vertex* vertices;
        uint32_t vertexCount;

        Polygon() : vertices(nullptr), vertexCount(0) {};
        Polygon(ThreeD::Vertex* vertices, uint32_t vertexCount) : vertices(vertices), vertexCount(vertexCount) {};

        void Render(GLShader* shader) const{
            uint32_t program =
                    shader->GetProgram();
            glUseProgram(program);

            const int32_t POSITION = glGetAttribLocation(
                    program, "a_Position");
            const int32_t COLOR = glGetAttribLocation(
                    program, "a_Color");

            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 3, GL_DOUBLE, false,
                                  sizeof(ThreeD::Vertex),
                                  &vertices->position);
            glEnableVertexAttribArray(COLOR);
            glVertexAttribPointer(COLOR, 3, GL_DOUBLE, false,
                                  sizeof(ThreeD::Vertex),
                                  &vertices->color);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    };
}