//
// Created by Mathis on 20/05/2023.
//

#pragma once

#include <cstdint>
#include "Vertex.hpp"
#include "Polygon.hpp"

namespace ThreeD {
    struct Mesh{
        ThreeD::Polygon* polygons;
        uint32_t polygonCount;

        Mesh() : polygons(nullptr), polygonCount(0) {};
        Mesh(ThreeD::Polygon* polygons, uint32_t polygonCount) : polygons(polygons), polygonCount(polygonCount) {};

        void Render(GLShader* shader) const{
            for (int i = 0; i < polygonCount; i++) {
                polygons[i].Render(shader);
            }
        }
    };
}