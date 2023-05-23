#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include "../shaders/GLShader.hpp"
#include "../ThreeD/Vertex.hpp"
#include "../math/Matrix.hpp"
#include "../ThreeD/Camera.h"

namespace Window {
    struct Application
    {
        struct Light{
            Math::Vector3 position;
            Math::Vector3 ambient;
            Math::Vector3 diffuse;
            Math::Vector3 specular;
            Math::Vector3 color;
        } light;

        bool initialize()
        {
            std::cout << "Pilote : " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;

            GLenum error = glewInit();

            light.position = Math::Vector3(0.0f, 0.9f, 0.0f);
            light.ambient = Math::Vector3(0.5f, 0.5f, 0.5f);
            light.diffuse = Math::Vector3(0.5f, 0.5f, 0.5f);
            light.specular = Math::Vector3(1.0f, 1.0f, 1.0f);
            light.color = Math::Vector3(1.0f, 1.0f, 1.0f);


            return true;
        }

        void deinitialize(ThreeD::Mesh* meshes, uint32_t meshCount)
        {
            for (int i = 0; i < meshCount; ++i) {
                meshes[i].shader->Destroy();
            }
        }

        void render(GLFWwindow* window, ThreeD::Mesh* meshes, uint32_t meshCount, Camera& camera) {
            int width, height;
            GLenum err;
            glfwGetWindowSize(window, &width, &height);

            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);

            glViewport(0, 0, width, height);
            glClearColor(0.4f, 0.4f, 0.65f, 1.f);

            const int stride = sizeof(ThreeD::Vertex);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (int i = 0; i < meshCount; ++i) {
                std::cerr << "Mesh " << i << ": " << meshes[i].name << std::endl;
                float time = glfwGetTime();

                const auto program = meshes[i].shader->GetProgram();
                glUseProgram(program);

                //TIME
                const auto TIME = glGetUniformLocation(program,"u_time");
                glUniform1f(TIME, time);

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on time: " << err << std::endl;
                }

                //TRANSFORM
                // une matrice OpenGL est definie en COLONNE
                float rotationMatrix[16] = {
                        cosf(time), 0.f, -sinf(time), 0.0f,
                        0.f, 1.f, 0.0f, 0.0f,
                        sinf(time), 0.0f, cosf(time), 0.0f,
                        0.0f, 0.0f, -20.0f, 1.0f
                };

                const auto ROT_MAT = glGetUniformLocation(program, "u_rotationMatrix");
                glUniform4f(ROT_MAT, meshes[i].rotation.getS(), meshes[i].rotation.getI(), meshes[i].rotation.getJ(), meshes[i].rotation.getK());


                const auto MESH_POS = glGetUniformLocation(program, "u_meshPosition");
                glUniform3f(MESH_POS, meshes[i].position.getX(), meshes[i].position.getY(), meshes[i].position.getZ());

                const auto MESH_SCAL = glGetUniformLocation(program, "u_scale");
                glUniform3f(MESH_SCAL, meshes[i].scale.getX(), meshes[i].scale.getY(), meshes[i].scale.getZ());

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on transform: " << err << std::endl;
                }




                //CAMERA

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


                const auto CAM_TRANS = glGetUniformLocation(program, "camPos");
                glUniform3f(CAM_TRANS, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

                const auto CAM_ROT = glGetUniformLocation(program, "camRot");
                glUniform4f(CAM_ROT, camera.getRotation().getS(), camera.getRotation().getI(), camera.getRotation().getJ(), camera.getRotation().getK());

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on camera: " << err << std::endl;
                }

                //Texture
                const auto TEX_COORD = glGetAttribLocation(program,"a_texCoord");
                glVertexAttribPointer(TEX_COORD, 2, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->texcoords);

                if(meshes[i].material.texture != nullptr){
                    glBindTexture(GL_TEXTURE_2D, meshes[i].material.texture->id);
                    //TODO:
                    //glBindVertexArray(VAO);
                }

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on texture: " << err << std::endl;
                }

                //VERTEX
                const auto POSITION = glGetAttribLocation(program,"a_position");
                glEnableVertexAttribArray(POSITION);
                glVertexAttribPointer(POSITION, 3, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->position);

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on vertex position: " << err << std::endl;
                }

                const auto COLOR = glGetAttribLocation(program,"a_color");
                glEnableVertexAttribArray(COLOR);
                glVertexAttribPointer(COLOR, 3, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->normal);

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on vertex color: " << err << std::endl;
                }


                //LIGHT
                auto* lightPosition = new GLfloat[3] {(float) light.position.x, (float) light.position.y, (float) light.position.z};
                const auto LIGHT_POSITION = glGetUniformLocation(program,"u_light.position");
                glUniform3fv(LIGHT_POSITION, 1, lightPosition);

                auto* lightAmbient = new GLfloat[3] {(float) light.ambient.x, (float) light.ambient.y, (float) light.ambient.z};
                const auto LIGHT_AMBIENT = glGetUniformLocation(program,"u_light.ambient");
                glUniform3fv(LIGHT_AMBIENT, 1, lightAmbient);

                auto* lightDiffuse = new GLfloat[3] {(float) light.diffuse.x, (float) light.diffuse.y, (float) light.diffuse.z};
                const auto LIGHT_DIFFUSE = glGetUniformLocation(program,"u_light.diffuse");
                glUniform3fv(LIGHT_DIFFUSE, 1, lightDiffuse);

                auto * lightSpecular = new GLfloat[3] {(float) light.specular.x, (float) light.specular.y, (float) light.specular.z};
                const auto LIGHT_SPECULAR = glGetUniformLocation(program,"u_light.specular");
                glUniform3fv(LIGHT_SPECULAR, 1, lightSpecular);

                auto * lightColor = new GLfloat[3] {(float) light.color.x, (float) light.color.y, (float) light.color.z};
                const auto LIGHT_COLOR = glGetUniformLocation(program,"u_light.color");
                glUniform3fv(LIGHT_COLOR, 1, lightColor);

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on light: " << err << std::endl;
                }

                //MATERIAL
                auto* materialAmbient = new GLfloat[3] {(float) meshes[i].material.ambient.x, (float) meshes[i].material.ambient.y, (float) meshes[i].material.ambient.z};
                const auto MATERIAL_AMBIENT = glGetUniformLocation(program,"u_material.ambient");
                glUniform3fv(MATERIAL_AMBIENT, 1, materialAmbient);

                auto* materialDiffuse = new GLfloat[3] {(float) meshes[i].material.diffuse.x, (float) meshes[i].material.diffuse.y, (float) meshes[i].material.diffuse.z};
                const auto MATERIAL_DIFFUSE = glGetUniformLocation(program,"u_material.diffuse");
                glUniform3fv(MATERIAL_DIFFUSE, 1, materialDiffuse);

                auto* materialSpecular = new GLfloat[3] {(float) meshes[i].material.specular.x, (float) meshes[i].material.specular.y, (float) meshes[i].material.specular.z};
                const auto MATERIAL_SPECULAR = glGetUniformLocation(program,"u_material.specular");
                glUniform3fv(MATERIAL_SPECULAR, 1, materialSpecular);

                const auto MATERIAL_SHININESS = glGetUniformLocation(program,"u_material.shininess");
                glUniform1f(MATERIAL_SHININESS, meshes[i].material.shininess);

                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on mat: " << err << std::endl;
                }

                //DRAW
                glDrawElements(GL_TRIANGLES, meshes[i].indicesCount, GL_UNSIGNED_SHORT, meshes[i].indices);
                while ((err = glGetError()) != GL_NO_ERROR) {
                    std::cerr << "OpenGL error on draw: " << err << std::endl;
                }
                std::cerr << "Mesh Drawn" << std::endl << std::endl;
            }
        }
    };
}