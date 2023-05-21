#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include "../shaders/GLShader.hpp"
#include "../ThreeD/Vertex.hpp"
#include "../math/Matrix.hpp"

namespace Window {
    struct Application
    {
        GLShader m_basicShader;

        bool initialize()
        {
            std::cout << "Pilote : " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;

            GLenum error = glewInit();

            m_basicShader.LoadVertexShader(
                    "../shaders/basic/basic.vs.glsl"
            );
            m_basicShader.LoadFragmentShader(
                    "../shaders/basic/basic.fs.glsl"
            );
            m_basicShader.Create();

            return true;
        }

        void deinitialize()
        {
            m_basicShader.Destroy();
        }

        void render(GLFWwindow* window, ThreeD::Mesh* meshes, uint32_t meshCount) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);

            glViewport(0, 0, width, height);
            glClearColor(0.0f, 0.0f, 0.0f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            float time = glfwGetTime();

            const auto program = m_basicShader.GetProgram();
            glUseProgram(program);

            // une matrice OpenGL est definie en COLONNE
            float rotationMatrix[16] = {
                    cosf(time), 0.f, -sinf(time), 0.0f,
                    0.f, 1.f, 0.0f, 0.0f,
                    sinf(time), 0.0f, cosf(time), 0.0f,
                    0.0f, 0.0f, -20.0f, 1.0f
            };

            const auto loc_rotz_mat = glGetUniformLocation(program, "u_rotationMatrix");
            glUniformMatrix4fv(loc_rotz_mat, 1, GL_FALSE, rotationMatrix);

            const float aspectRatio = float(width)/float(height);
            const float zNear = 0.1f, zFar = 100.0f;
            const float fovy = 45.f * M_PI/180.f;
            const float cot = 1.f / tanf(fovy / 2.f);
            float projectionMatrix[] = {
                    cot/aspectRatio, 0.f, 0.f, 0.f, // 1ere colonne
                    0.f, cot, 0.f, 0.f,
                    0.f, 0.f, -zFar/(zFar-zNear), -1.f,
                    0.f, 0.f, -zFar*zNear/(zFar-zNear), 0.f
            };

            const auto PROJ_MAT = glGetUniformLocation(program, "u_projectionMatrix");
            glUniformMatrix4fv(PROJ_MAT, 1, GL_FALSE, projectionMatrix);

            const auto POSITION = glGetAttribLocation(program,"a_position");
            const auto COLOR = glGetAttribLocation(program,"a_color");

            const int stride = sizeof(ThreeD::Vertex);

            for (int i = 0; i < meshCount; ++i) {
                glVertexAttribPointer(POSITION, 3, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->position);
                glEnableVertexAttribArray(POSITION);

                glVertexAttribPointer(COLOR, 3, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->normal);
                glEnableVertexAttribArray(COLOR);

                const auto loc_time = glGetUniformLocation(program,"u_time");
                glUniform1f(loc_time, time);

                glDrawElements(GL_TRIANGLES, meshes[i].indicesCount, GL_UNSIGNED_SHORT, meshes[i].indices);
            }
        }
    };
}