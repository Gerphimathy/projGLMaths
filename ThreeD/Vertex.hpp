#pragma once
#include "../math/Vector3.hpp"
#include "../math/Vector2.hpp"

namespace ThreeD {
    struct Vertex{
        Math::Vector3 position;
        Math::Vector3 normal;
        Math::Vector2 texcoords;
    };
}