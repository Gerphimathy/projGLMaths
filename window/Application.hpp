#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include "../shaders/GLShader.hpp"
#include "../ThreeD/Vertex.hpp"
#include "../math/Matrix.hpp"
#include "../ThreeD/Camera.h"
#include "../ThreeD/Light.h"

namespace Window {

    void GLAPIENTRY
    MessageCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam ){

        fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                 ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                 type, severity, message );
    }

    struct Application
    {


        bool initialize()
        {
            std::cout << "Pilote : " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "OpenGL : " << glGetString(GL_VERSION) << std::endl;

            GLenum error = glewInit();

            glEnable(GL_DEBUG_OUTPUT);
            //glDebugMessageCallback(MessageCallback, 0);



            return true;
        }

        void deinitialize(ThreeD::Mesh* meshes, uint32_t meshCount)
        {
            for (int i = 0; i < meshCount; ++i) {
                meshes[i].shader->Destroy();
                delete [] meshes[i].vertices;
                if (meshes[i].material.texture)
                    glDeleteTextures(1, &meshes[i].material.texture->id);
            }
        }

        void GLReportError(std::string value){
            GLenum err;

            while ((err = glGetError()) != GL_NO_ERROR) {
                std::cerr << "OpenGL error on " << value << ": " << err << std::endl;
            }
        }

        void render(GLFWwindow* window, ThreeD::Mesh* meshes, uint32_t meshCount, ThreeD::Camera& camera, ThreeD::Light& light, bool verbose = false) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            if(verbose) std::cout << "Camera Position: " << camera.position << std::endl;

            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);

            glViewport(0, 0, width, height);
            glClearColor(0.4f, 0.4f, 0.65f, 1.f);

            const int stride = sizeof(ThreeD::Vertex);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (int i = 0; i < meshCount; ++i) {
                if(verbose) std::cerr << "Mesh " << i << ": " << meshes[i].name << std::endl;
                float time = glfwGetTime();

                const auto program = meshes[i].shader->GetProgram();
                glUseProgram(program);

                //TIME
                const auto TIME = glGetUniformLocation(program,"u_time");
                glUniform1f(TIME, time);
                GLReportError("Time");


                //TRANSFORM
                // une matrice OpenGL est definie en COLONNE


                /*

                const auto MESH_ROT = glGetUniformLocation(program, "u_meshRotation");
                glUniform4f(MESH_ROT, meshes[i].rotation.getI(), meshes[i].rotation.getJ(), meshes[i].rotation.getK(), meshes[i].rotation.getS());
                GLReportError("Mesh Rotation");

                const auto MESH_POS = glGetUniformLocation(program, "u_meshPosition");
                glUniform3f(MESH_POS, meshes[i].position.getX(), meshes[i].position.getY(), meshes[i].position.getZ());
                GLReportError("Mesh Position");

                const auto MESH_SCAL = glGetUniformLocation(program, "u_scale");
                glUniform3f(MESH_SCAL, meshes[i].scale.getX(), meshes[i].scale.getY(), meshes[i].scale.getZ());
                GLReportError("Mesh Scale");

                */

                const Math::Matrix4_4 rotMat = meshes[i].rotation.ToMatrix();
                Math::Matrix4_4 posMat = Math::Matrix4_4();
                const Math::Vector3 pos = meshes[i].position;
                posMat.set(pos.x, 0, 3);
                posMat.set(pos.y, 1, 3);
                posMat.set(pos.z, 2, 3);
                Math::Matrix4_4 scalMat = Math::Matrix4_4();
                const Math::Vector3 scal = meshes[i].scale;
                scalMat.set(scal.x, 0, 0);
                scalMat.set(scal.y, 1, 1);
                scalMat.set(scal.z, 2, 2);

                Math::Matrix4_4 worldMat = Math::Matrix4_4();
                worldMat = scalMat * worldMat;
                worldMat = rotMat * worldMat;
                worldMat = posMat * worldMat;


                const auto WORLD_MAT = glGetUniformLocation(program, "u_worldMatrix");
                glUniformMatrix4fv(WORLD_MAT, 1, GL_FALSE, worldMat.ToArray().data());



                //CAMERA



                const auto PROJ_MAT = glGetUniformLocation(program, "u_projectionMatrix");
                glUniformMatrix4fv(PROJ_MAT, 1, GL_FALSE, camera.projectionMatrix.ToArray().data());
                GLReportError("Projection Matrix");

                /*

                const auto CAM_TRANS = glGetUniformLocation(program, "camPos");
                glUniform3f(CAM_TRANS, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
                GLReportError("Camera Position");

                const auto CAM_ROT = glGetUniformLocation(program, "camRot");
                glUniform4f(CAM_ROT, -camera.getRotation().getI(), -camera.getRotation().getJ(), -camera.getRotation().getK(), camera.getRotation().getS());
                GLReportError("Camera Rotation");

                 */

                const auto VIEW_MAT = glGetUniformLocation(program, "u_viewMatrix");
                Math::Matrix4_4 camPosMat = Math::Matrix4_4();
                Math::Vector3 camPos = camera.position;
                camPosMat.set(-(camPos.x), 0, 3);
                camPosMat.set(-(camPos.y), 1, 3);
                camPosMat.set(-(camPos.z), 2, 3);
                const Math::Matrix4_4 viewMat = camera.rotation.ToMatrix().Transpose() * camPosMat;
                glUniformMatrix4fv(VIEW_MAT, 1, GL_FALSE, viewMat.ToArray().data());

                //Texture
                const auto TEX_COORD = glGetAttribLocation(program,"a_texCoord");
                glEnableVertexAttribArray(TEX_COORD);
                glVertexAttribPointer(TEX_COORD, 2, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->texcoords);
                GLReportError("Texture Coordinates");

                float texFlag = (meshes[i].material.texture != nullptr) ? 1.0f : 0.0f;
                const auto USE_TEXTURE = glGetUniformLocation(program, "u_usetexture");
                glUniform1f(USE_TEXTURE, texFlag);
                GLReportError("Use Texture");

                if(meshes[i].material.texture != nullptr){
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, meshes[i].material.texture->id);

                    const auto TEXTURE = glGetUniformLocation(program, "u_texture");
                    glUniform1i(TEXTURE, 0);

                    GLReportError("Texture");
                }

                //VERTEX
                const auto POSITION = glGetAttribLocation(program,"a_position");
                glEnableVertexAttribArray(POSITION);
                glVertexAttribPointer(POSITION, 3, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->position);
                GLReportError("Vertex Position");

                const auto NORMAL = glGetAttribLocation(program,"a_normal");
                glEnableVertexAttribArray(NORMAL);
                glVertexAttribPointer(NORMAL, 3, GL_DOUBLE, GL_FALSE, stride, &meshes[i].vertices->normal);
                GLReportError("Vertex Normal");


                //LIGHT
                auto* lightPosition = new GLfloat[3] {(float) light.position.x, (float) light.position.y, (float) light.position.z};
                const auto LIGHT_POSITION = glGetUniformLocation(program,"u_light.position");
                glUniform3fv(LIGHT_POSITION, 1, lightPosition);
                GLReportError("Light Position");

                auto* lightAmbient = new GLfloat[3] {(float) light.ambient.x, (float) light.ambient.y, (float) light.ambient.z};
                const auto LIGHT_AMBIENT = glGetUniformLocation(program,"u_light.ambient");
                glUniform3fv(LIGHT_AMBIENT, 1, lightAmbient);
                GLReportError("Light Ambient");

                auto* lightDiffuse = new GLfloat[3] {(float) light.diffuse.x, (float) light.diffuse.y, (float) light.diffuse.z};
                const auto LIGHT_DIFFUSE = glGetUniformLocation(program,"u_light.diffuse");
                glUniform3fv(LIGHT_DIFFUSE, 1, lightDiffuse);
                GLReportError("Light Diffuse");

                auto * lightSpecular = new GLfloat[3] {(float) light.specular.x, (float) light.specular.y, (float) light.specular.z};
                const auto LIGHT_SPECULAR = glGetUniformLocation(program,"u_light.specular");
                glUniform3fv(LIGHT_SPECULAR, 1, lightSpecular);
                GLReportError("Light Specular");

                auto * lightColor = new GLfloat[3] {(float) light.color.x, (float) light.color.y, (float) light.color.z};
                const auto LIGHT_COLOR = glGetUniformLocation(program,"u_light.color");
                glUniform3fv(LIGHT_COLOR, 1, lightColor);
                GLReportError("Light Color");

                //MATERIAL
                auto* materialAmbient = new GLfloat[3] {(float) meshes[i].material.ambient.x, (float) meshes[i].material.ambient.y, (float) meshes[i].material.ambient.z};
                const auto MATERIAL_AMBIENT = glGetUniformLocation(program,"u_material.ambient");
                glUniform3fv(MATERIAL_AMBIENT, 1, materialAmbient);
                GLReportError("Material Ambient");

                auto* materialDiffuse = new GLfloat[3] {(float) meshes[i].material.diffuse.x, (float) meshes[i].material.diffuse.y, (float) meshes[i].material.diffuse.z};
                const auto MATERIAL_DIFFUSE = glGetUniformLocation(program,"u_material.diffuse");
                glUniform3fv(MATERIAL_DIFFUSE, 1, materialDiffuse);
                GLReportError("Material Diffuse");

                auto* materialSpecular = new GLfloat[3] {(float) meshes[i].material.specular.x, (float) meshes[i].material.specular.y, (float) meshes[i].material.specular.z};
                const auto MATERIAL_SPECULAR = glGetUniformLocation(program,"u_material.specular");
                glUniform3fv(MATERIAL_SPECULAR, 1, materialSpecular);
                GLReportError("Material Specular");

                const auto MATERIAL_SHININESS = glGetUniformLocation(program,"u_material.shininess");
                glUniform1f(MATERIAL_SHININESS, meshes[i].material.shininess);
                GLReportError("Material Shininess");

                //DRAW
                glDrawElements(GL_TRIANGLES, meshes[i].indicesCount, GL_UNSIGNED_SHORT, meshes[i].indices);
                GLReportError("Draw");

                if(verbose) std::cerr << "Mesh Drawn" << std::endl << std::endl;
            }
        }
    };



}