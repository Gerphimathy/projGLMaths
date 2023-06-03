#pragma once

#include "Vertex.hpp"
#include "../math/Vector2.hpp"

namespace ThreeD{
    struct Polygon{
        Vertex* vertices;
        Math::Vector2* texcoords;
        uint32_t vertexCount;
    };
}