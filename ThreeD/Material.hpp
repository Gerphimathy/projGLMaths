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
    };
}