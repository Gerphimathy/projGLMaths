//
// Created by yanis on 23/05/2023.
//
#include "../Math/Vector3.hpp"
#include "../Math/Quaternion.hpp"

#ifndef MATH_CAMERA_H
#define MATH_CAMERA_H


class Camera {

public:
    Math::Vector3 position;
    Math::Quaternion rotation;

    Camera(const Math::Vector3 &position, const Math::Quaternion &rotation);

    Camera();

    const Math::Vector3 &getPosition() const;

    void setPosition(const Math::Vector3 &position);

    const Math::Quaternion &getRotation() const;

    void setRotation(const Math::Quaternion &rotation);
};




#endif //MATH_CAMERA_H
