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

        Math::Vector3 position;

        uint16_t* indices;
        uint32_t indicesCount;

        //Material
        GLShader* shader;

        void CastFromArray(const float* array, int size);

        void loadShader(const char* vertexShader, const char* fragmentShader);
    };
}