#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include "../shaders/GLShader.hpp"
#include "../ThreeD/Vertex.hpp"

namespace Window {
    struct Application
    {
        GLShader m_basicShader;

        int m_width = 1280;
        int m_height = 720;

        inline void setSize(int width, int height) {
            m_width = width;
            m_height = height;
        }

        bool initialize()
        {
            std::cout << "Pilote : " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;

            GLenum error = glewInit();

            return true;
        }

        void deinitialize()
        {
            m_basicShader.Destroy();
        }

        void render()
        {
            glEnable(GL_SCISSOR_TEST);

            glViewport(0, 0, m_width, m_height);
            glScissor(0, 0, m_width, m_height);

            glClear(GL_COLOR_BUFFER_BIT);

            uint32_t program =
                    m_basicShader.GetProgram();
            glUseProgram(program);

            const int32_t POSITION = glGetAttribLocation(
                    program, "a_Position");
            const int32_t COLOR = glGetAttribLocation(
                    program, "a_Color");

            const auto temps = static_cast<float>(
                    glfwGetTime());
            const int32_t TIME =
                    glGetUniformLocation(program, "u_Time");
            glUniform1f(TIME, temps);


            glDisable(GL_SCISSOR_TEST);
        }
    };
}