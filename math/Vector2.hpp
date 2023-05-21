//
// Created by yanis on 10/05/2023.
//

#ifndef OPENGL_101_VECTOR2_HPP
#define OPENGL_101_VECTOR2_HPP

namespace Math {

    struct Vector2 {

        double x;
        double y;

        Vector2(double x, double y);

        Vector2() : Vector2(0, 0) {};

        double getX() const;

        void setX(double x);

        double getY() const;

        void setY(double y);

        double Norm();

        double operator[](int i) const { return (&x)[i]; }
    };



}
#endif //OPENGL_101_VECTOR2_HPP
