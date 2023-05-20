//
// Created by Mathis on 20/05/2023.
//

#pragma once
#include "../math/Vector3.hpp"
#include "../math/Vector2.hpp"

namespace ThreeD {
    struct Vertex{
        Math::Vector3 position;
        Math::Vector3 color;
        Math::Vector3 normal;
        Math::Vector2 texcoords;

        Vertex() : position(Math::Vector3()), normal(Math::Vector3()), color(Math::Vector3(255,255,255)), texcoords(Math::Vector2()) {};
        explicit Vertex(Math::Vector3 pos) : position(pos), normal(Math::Vector3()), color(Math::Vector3(255,255,255)), texcoords(Math::Vector2()) {};
        Vertex(Math::Vector3 pos, Math::Vector3 col) : position(pos), normal(Math::Vector3()), color(col), texcoords(Math::Vector2()) {};
    };
}