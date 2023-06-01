//
// Created by yanis on 29/05/2023.
//

#include "ThreeDObject.h"
namespace ThreeD {
    ThreeDObject::ThreeDObject() {
        position = {0, 0, 0};
        rotation = Math::Quaternion::Euler(0,0,0);
    }

    ThreeDObject::ThreeDObject(const Math::Vector3 &position, const Math::Quaternion &rotation) : position(position),
                                                                                      rotation(rotation) {}

    const Math::Vector3 &ThreeDObject::getPosition() const {
        return position;
    }

    void ThreeDObject::setPosition(const Math::Vector3 &position) {
        ThreeDObject::position = position;
    }

    const Math::Quaternion &ThreeDObject::getRotation() const {
        return rotation;
    }

    void ThreeDObject::setRotation(const Math::Quaternion &rotation) {
        ThreeDObject::rotation = rotation;
    }

    Math::Vector3 ThreeDObject::forward() const {
        return (rotation * Math::Vector3{ 0, 0, 1 }).Normalized();
    }

    Math::Vector3 ThreeDObject::right() const {
        return (rotation * Math::Vector3{ 1, 0, 0 }).Normalized();
    }

    Math::Vector3 ThreeDObject::up() const {
        return (rotation * Math::Vector3{ 0, 1, 0 }).Normalized();
    }

    void ThreeDObject::rotate(const Math::Quaternion q){
        rotation *= q;
        rotation.Normalize();
    }

    void ThreeDObject::rotateByAxisAndAngle(const Math::Vector3 u, const double angle){
        double c = cos(angle);
        double s = sin(angle);
        Math::Quaternion q = {c, u.x * s, u.y * s, u.z * s};
        rotate(q);
    }

}
