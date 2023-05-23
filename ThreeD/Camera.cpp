//
// Created by yanis on 23/05/2023.
//

#include "Camera.h"

Camera::Camera(const Math::Vector3 &position, const Math::Quaternion &rotation) : position(position),
                                                                                  rotation(rotation) {}

Camera::Camera() {
    position = {0,0,0};
    rotation = {1, 0, 0, 0};
}

const Math::Vector3 &Camera::getPosition() const {
    return position;
}

void Camera::setPosition(const Math::Vector3 &position) {
    Camera::position = position;
}

const Math::Quaternion &Camera::getRotation() const {
    return rotation;
}

void Camera::setRotation(const Math::Quaternion &rotation) {
    Camera::rotation = rotation;
}
