#include <iostream>
#include "Mesh.hpp"
#include "../shaders/GLShader.hpp"

namespace ThreeD{
    void Mesh::CastFromArray(const float* vertexArray, const uint16_t* indices, int sizeVertices, int sizeIndices){
        vertexCount = sizeVertices/8;
        vertices = new Math::Vector3[vertexCount];

        normalCount = sizeVertices/8;
        normals = new Math::Vector3[normalCount];

        uvCount = sizeVertices/8;
        uvs = new Math::Vector2[uvCount];

        for(int i = 0; i < vertexCount; i++){
            vertices[i] = {vertexArray[i*8], vertexArray[i*8+1], vertexArray[i*8+2]};

            normals[i] = {vertexArray[i*8+3], vertexArray[i*8+4], vertexArray[i*8+5]};

            uvs[i] = {vertexArray[i * 8 + 6], vertexArray[i * 8 + 7]};
        }

        triangleCount = sizeIndices/3;
        triangles = new Triangle[triangleCount];
        for (int i = 0; i < triangleCount; ++i) {
            triangles[i].vertex_indices[0] = indices[i*3];
            triangles[i].vertex_indices[1] = indices[i*3+1];
            triangles[i].vertex_indices[2] = indices[i*3+2];

            triangles[i].normal_indices[0] = indices[i*3];
            triangles[i].normal_indices[1] = indices[i*3+1];
            triangles[i].normal_indices[2] = indices[i*3+2];

            triangles[i].uv_indices[0] = indices[i*3];
            triangles[i].uv_indices[1] = indices[i*3+1];
            triangles[i].uv_indices[2] = indices[i*3+2];

            triangles[i].material_index = 0;
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

        normals = nullptr;
        normalCount = 0;

        uvs = nullptr;
        uvCount = 0;

        triangles = nullptr;
        triangleCount = 0;

        materials = nullptr;
        materialCount = 0;

        position = {0,0,0};
        rotation = Math::Quaternion::Euler(0,0,0);
        scale = {1, 1 ,1};
        shader = nullptr;

        name="";
    }


}