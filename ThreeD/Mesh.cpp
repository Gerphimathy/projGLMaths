#include <iostream>
#include "Mesh.hpp"
#include "../shaders/GLShader.hpp"

namespace ThreeD{
    void Mesh::CastFromArray(const float* array, int size){
        vertexCount = size/8;
        vertices = new ThreeD::Vertex[vertexCount];

        for(int i = 0; i < vertexCount; i++){
            vertices[i].position = {array[i*8], array[i*8+1], array[i*8+2]};

            vertices[i].normal = {array[i*8+3], array[i*8+4], array[i*8+5]};

            vertices[i].texcoords = {array[i * 8 + 6], array[i * 8 + 7]};
        }
    }

    void Mesh::loadShader(const char* vertexShader, const char* fragmentShader){
        shader = new GLShader();
        shader->LoadVertexShader(
                vertexShader
        );
        shader->LoadFragmentShader(
                fragmentShader
        );
        shader->Create();
    }

    Mesh::Mesh() {
        vertices = nullptr;
        vertexCount = 0;
        position = {0,0,0};
        rotation = Math::Quaternion::Euler(0,0,0);
        scale = {1, 1 ,1};
        indices = nullptr;
        indicesCount = 0;
        shader = nullptr;
        material = Material();

        name="";
    }

}