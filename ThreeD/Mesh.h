//
// Created by Mathis on 20/05/2023.
//

#pragma once

#include <cstdint>
#include "Vertex.hpp"

namespace ThreeD {
    struct Mesh{
        ThreeD::Vertex* vertices;
        uint32_t* vertexCount;
    };
}