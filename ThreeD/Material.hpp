#pragma once
#include "../math/Vector3.hpp"
#include "Texture.hpp"

namespace ThreeD {
    struct Material {
        Math::Vector3 ambient;
        Math::Vector3 diffuse;
        Math::Vector3 specular;
        float shininess;

        std::string name;

        Texture* texture;

        Material(){
            ambient = {0.1f, 0.1f, 0.1f};
            diffuse = {1.0f, 1.0f, 1.0f};
            specular = {0.5f, 0.5f, 0.5f};
            shininess = 32.0f;
            texture = nullptr;
        }
    };
}