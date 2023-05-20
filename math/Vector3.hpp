//
// Created by yanis on 10/05/2023.
//

#ifndef OPENGL_101_VECTOR3_HPP
#define OPENGL_101_VECTOR3_HPP

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
    };

} // Math

#endif //OPENGL_101_VECTOR3_HPP
