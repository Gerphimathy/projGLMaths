//
// Created by Mathis on 20/05/2023.
//

#pragma once

#include <cstdint>
#include "Vertex.hpp"
#include "../shaders/GLShader.hpp"

namespace ThreeD {
    struct Mesh{
        ThreeD::Vertex* vertices;
        uint32_t vertexCount;

        void Render(GLShader *shader){
            static float alpha = 0;
            //attempt to rotate cube
            glRotatef(alpha, 0, 1, 0);
            alpha += 0.5f;

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

            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        }
    };
}