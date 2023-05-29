//
// Created by yanis on 23/05/2023.
//

#include "Camera.h"
namespace ThreeD {
    Camera::Camera(const Math::Vector3 &position, const Math::Quaternion &rotation) : ThreeDObject(position, rotation) {}

    Camera::Camera() : ThreeDObject() {
        projectionMatrix = Math::Matrix4_4();
    }

}