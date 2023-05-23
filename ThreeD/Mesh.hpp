//
// Created by Mathis on 20/05/2023.
//

#pragma once

#include <cstdint>
#include "Vertex.hpp"
#include "Material.hpp"
#include "../shaders/GLShader.hpp"
#include "../math/Quaternion.hpp"

namespace ThreeD {
    struct Mesh{
        ThreeD::Vertex* vertices;
        uint32_t vertexCount;

        Math::Vector3 position;
        Math::Quaternion rotation;
        Math::Vector3 scale;

        uint16_t* indices;
        uint32_t indicesCount;

        //Material
        GLShader* shader;
        Material material;

        std::string name;

        void CastFromArray(const float* array, int size);

        void loadShader(const char* vertexShader, const char* fragmentShader);

        Mesh();
    };
}