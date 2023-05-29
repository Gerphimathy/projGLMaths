//
// Created by yanis on 10/05/2023.
//

#ifndef OPENGL_101_VECTOR3_HPP
#define OPENGL_101_VECTOR3_HPP

#include <iostream>

namespace Math {

    struct Vector3 {

        double x;
        double y;
        double z;

        Vector3(double x, double y, double z);

        Vector3() : Vector3(0, 0, 0) {};

        double getX() const;

        void setX(double x);

        double getY() const;

        void setY(double y);

        double getZ() const;

        void setZ(double z);

        double Norm();

        double operator[](int i) const { return (&x)[i]; };

        bool operator==(const Vector3 &rhs) const;

        bool operator!=(const Vector3 &rhs) const;

        Vector3 operator+=(const Vector3 &rhs);

        Vector3 operator-=(const Vector3 &rhs);

        Vector3 operator-() const;

        Vector3 operator*=(const double& i);

        Vector3 operator*(const double& i) const;

        Vector3 operator+(const Vector3& v) const;

        static double dotProduct(const Vector3 &u, const Vector3 &v);

        static Vector3 crossProduct(const Vector3 &u, const Vector3 &v);
    };

} // Math

#endif //OPENGL_101_VECTOR3_HPP
