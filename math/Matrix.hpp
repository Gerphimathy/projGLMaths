//
// Created by Mathis on 20/05/2023.
//

#pragma once
#include <array>
#include <ostream>
#include <cmath>
#include "Quaternion.hpp"

namespace Math{
    class Quaternion;

    class Matrix4_4
    {
        private:
            std::array<std::array<double, 4>, 4> matrix{};
        public:

            // Constructors
            Matrix4_4();
            explicit Matrix4_4(std::array<std::array<double, 4>, 4> matrix);
            Matrix4_4(Matrix4_4 const &matrix);

            //Setters/Getters
            std::array<std::array<double, 4>, 4> getMatrix() const;
            void setMatrix(std::array<std::array<double, 4>, 4> m);
            void setMatrix(const Matrix4_4& m);

            //Row|Lines Setters/Getters
            std::array<double , 4> getLine(int i) const;
            void setLine(std::array<double , 4> line, int i);

            std::array<double, 4> getColumn(int j) const;
            void setColumn(std::array<double, 4> row, int j);

            //Value Setters/Getters
            void set(double value, int i, int j);
            double get(int i, int j) const;

            //Operators
            Matrix4_4 operator+(const Matrix4_4& m) const;
            Matrix4_4 operator+=(const Matrix4_4& m);

            Matrix4_4 operator-(const Matrix4_4& m) const;
            Matrix4_4 operator-=(const Matrix4_4& m);
            Matrix4_4 operator-() const;

            Matrix4_4 operator*(const Matrix4_4& m) const;
            Matrix4_4 operator*=(const Matrix4_4& m);

            Matrix4_4 operator*(const double& d) const;
            Matrix4_4 operator*=(const double& d);

            Matrix4_4& operator=(const Matrix4_4& m);
            bool operator==(const Matrix4_4& m) const;
            bool operator!=(const Matrix4_4& m) const;

            friend std::ostream& operator<<(std::ostream& os, const Matrix4_4& m);

            //Conversions
            Quaternion ToQuaternion() const;

            //Functions
        std::array<float, 16> ToArray() const;

        static Matrix4_4 FromArray(std::array<float, 16>);

        Matrix4_4& operator=(const std::array<float, 16>);

        Matrix4_4 Transpose();
    };
}