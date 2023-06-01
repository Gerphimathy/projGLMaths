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

    double Vector3::Norm() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    Vector3 Vector3::Normalized() const
    {
        double norm = this->Norm();
        if(norm == 0.0)
        {
            return {};
        }
        return {x / norm, y / norm, z / norm};
    }

    double Vector3::dotProduct(const Vector3& u, const Vector3& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    Vector3 Vector3::crossProduct(const Vector3& u, const Vector3& v) {
        return{
                u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x
    };
    }



    bool Vector3::operator==(const Vector3 &rhs) const {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    bool Vector3::operator!=(const Vector3 &rhs) const {
        return !(rhs == *this);
    }

    Vector3 Vector3::operator+=(const Vector3 &rhs)  {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    Vector3 Vector3::operator-=(const Vector3 &rhs)  {
        *this += -rhs;
        return *this;
    }

    Vector3 Vector3::operator-() const  {
        return {-x, -y, -z};
    }

    Vector3 Vector3::operator*=(const double& i){
        x *= i;
        y *= i;
        z *= i;
        return *this;
    }

    Vector3 Vector3::operator*(const double& i) const{
        Vector3 temp = *this;
        temp *= i;
        return temp;
    }


    Vector3 Vector3::operator+(const Vector3& v) const{
        Vector3 temp = *this;
        temp += v;
        return temp;
    }

    std::ostream& operator<<(std::ostream& os, const Math::Vector3& v){
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

} // Math

