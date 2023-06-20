//
// Created by Mathis on 20/05/2023.
//

#pragma once

#include <cstdint>
#include "Material.hpp"
#include "../shaders/GLShader.hpp"
#include "../math/Quaternion.hpp"
#include "ThreeDObject.h"
#include "../math/Vector2.hpp"

namespace ThreeD {
    struct Triangle {
        uint16_t vertex_indices[3]{};
        uint16_t normal_indices[3]{};
        uint16_t uv_indices[3]{};
        uint16_t material_index;

        Triangle(){
            vertex_indices[0] = 0;
            vertex_indices[1] = 0;
            vertex_indices[2] = 0;

            normal_indices[0] = 0;
            normal_indices[1] = 0;
            normal_indices[2] = 0;

            uv_indices[0] = 0;
            uv_indices[1] = 0;
            uv_indices[2] = 0;

            material_index = 0;
        }
    };

    struct Mesh : public virtual ThreeDObject{
        Math::Vector3* vertices;
        uint32_t vertexCount;

        Math::Vector3* normals;
        uint32_t normalCount;

        Math::Vector2* uvs;
        uint32_t uvCount;

        Math::Vector3 scale;

        Triangle* triangles;
        uint32_t triangleCount;

        Material* materials;
        uint32_t materialCount;

        GLShader* shader;

        std::string name;

        //void CastFromArray(const float* array, int size);

        void loadShader(const char* vertexShader, const char* fragmentShader);

        Mesh();

    };
}