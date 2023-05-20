//
// Created by Mathis on 20/05/2023.
//

#pragma once
#include "../math/Vector3.hpp"
#include "../math/Vector2.hpp"

namespace ThreeD {
    struct Vertex{
        Math::Vector3 position;
        Math::Vector3 normal;
        Math::Vector3 color;
        Math::Vector2 texcoords;

        Vertex() : position(Math::Vector3(0, 0, 0)), normal(Math::Vector3(0, 0, 0)), color(Math::Vector3(0, 0, 0)), texcoords(Math::Vector2(0, 0)) {}
        Vertex(Math::Vector3 position, Math::Vector3 normal, Math::Vector3 color, Math::Vector2 texcoords) : position(position), normal(normal), color(color), texcoords(texcoords) {}
    };
}