#pragma once
#include "../math/Vector3.hpp"
#include "Texture.hpp"

namespace ThreeD {
    struct Material {
        Math::Vector3 ambient;
        Math::Vector3 diffuse;
        Math::Vector3 specular;
        float shininess;

        Texture* texture;

        std::string name;

        Material(){
            texture = nullptr;
            ambient = Math::Vector3(0.0f, 0.0f, 0.0f);
            diffuse = Math::Vector3(0.0f, 0.0f, 0.0f);
            specular = Math::Vector3(0.0f, 0.0f, 0.0f);

            shininess = 0.0f;
        }
    };
}