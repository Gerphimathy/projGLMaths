//
// Created by yanis on 10/05/2023.
//

#include <cmath>
#include "Vector3.hpp"

namespace Math {
    Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    double Vector3::getX() const {
        return x;
    }

    void Vector3::setX(double x) {
        Vector3::x = x;
    }

    double Vector3::getY() const {
        return y;
    }

    void Vector3::setY(double y) {
        Vector3::y = y;
    }

    double Vector3::getZ() const {
        return z;
    }

    void Vector3::setZ(double z) {
        Vector3::z = z;
    }

    double Vector3::Norm() {
        return std::sqrt(x*x + y*y + z*z);
    }
} // Math