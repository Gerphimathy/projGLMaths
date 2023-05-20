//
// Created by yanis on 10/05/2023.
//
#include <cmath>
#include "Vector2.hpp"

namespace Math{

    Vector2::Vector2(double x, double y) : x(x), y(y) {}

    double Vector2::getX() const {
        return x;
    }

    void Vector2::setX(double x) {
        Vector2::x = x;
    }

    double Vector2::getY() const {
        return y;
    }

    void Vector2::setY(double y) {
        Vector2::y = y;
    }

    double Vector2::Norm() {
        return std::sqrt(x*x + y*y);
    }



}