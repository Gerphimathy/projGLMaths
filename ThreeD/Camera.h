//
// Created by yanis on 23/05/2023.
//
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"
#include "ThreeDObject.h"

#ifndef MATH_CAMERA_H
#define MATH_CAMERA_H

namespace ThreeD {
    class Camera : public virtual ThreeDObject {

    public:

        Math::Matrix4_4 projectionMatrix;

        Camera(const Math::Vector3 &position, const Math::Quaternion &rotation);

        Camera();
    };

}


#endif //MATH_CAMERA_H
