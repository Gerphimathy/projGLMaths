//
// Created by yanis on 29/05/2023.
//

#ifndef MATH_LIGHT_H
#define MATH_LIGHT_H

#include "../math/Vector3.hpp"
#include "ThreeDObject.h"

namespace ThreeD {

    class Light : public virtual ThreeDObject{
    public:
        Math::Vector3 ambient;
        Math::Vector3 diffuse;
        Math::Vector3 specular;
        Math::Vector3 color;
    };

} // ThreeD

#endif //MATH_LIGHT_H
