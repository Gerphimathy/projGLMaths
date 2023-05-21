#include <iostream>
#include "Mesh.hpp"

namespace ThreeD{
    void Mesh::CastFromArray(const float* array, int size){
        vertexCount = size/8;
        vertices = new ThreeD::Vertex[vertexCount];

        for(int i = 0; i < vertexCount; i++){
            vertices[i].position = {array[i*8], array[i*8+1], array[i*8+2]};

            vertices[i].normal = {array[i*8+3], array[i*8+4], array[i*8+5]};

            vertices[i].uv = {array[i*8+6], array[i*8+7]};
        }
    }
}