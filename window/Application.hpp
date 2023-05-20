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

        void render(ThreeD::Mesh* meshes, uint32_t meshCount) {
            glEnable(GL_SCISSOR_TEST);

            glViewport(0, 0, m_width, m_height);
            glScissor(0, 0, m_width, m_height);

            glClearColor(0.f, 0.f, 0.f, 1.f);

            for (uint32_t i = 0; i < meshCount; ++i) {
                meshes[i].Render(&m_basicShader);
            }

            glDisable(GL_SCISSOR_TEST);
        }
    };
}