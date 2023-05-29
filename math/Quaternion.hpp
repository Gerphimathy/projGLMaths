#pragma once
#include <array>
#include <ostream>
#include <cmath>
#include "Matrix.hpp"
#include "Vector3.hpp"

namespace Math{
    class Matrix4_4;

    class Quaternion
    {
    private:
        double s;
        double i;
        double j;
        double k;
    public:

        //Constructors
        Quaternion() : s(0), i(0), j(0), k(0) {};
        [[maybe_unused]] Quaternion(double i, double j, double k) : s(0), i(i), j(j), k(k) {};
        Quaternion(double s, double i, double j, double k) : s(s), i(i), j(j), k(k) {}

        //Setters/Getters
        [[nodiscard]] double getS() const;
        [[maybe_unused]] void setS(double s);

        [[nodiscard]] double getI() const;
        [[maybe_unused]] void setI(double i);

        [[nodiscard]] double getJ() const;
        [[maybe_unused]] void setJ(double j);

        [[nodiscard]] double getK() const;
        [[maybe_unused]] void setK(double k);

        //Operators
        Quaternion operator+=(const Quaternion& q);
        Quaternion operator+(const Quaternion& q) const;

        Quaternion operator*=(const Quaternion& q);
        Quaternion operator*(const Quaternion& q) const;

        Quaternion operator*=(const double& d);
        Quaternion operator*=(const float &d);
        Quaternion operator*(const double& d) const;
        Quaternion operator*(const float& d) const;

        Quaternion operator^=(const Quaternion &q);
        Quaternion operator^(const Quaternion &q) const;

        Vector3 operator*(const Vector3& v) const;

        friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

        //Conversions
        Matrix4_4 ToMatrix() const;

        //Functions
        [[maybe_unused]] [[nodiscard]] Quaternion Conjugate() const;

        [[nodiscard]] double Norm() const;

        [[maybe_unused]] [[nodiscard]] Quaternion Normalized() const;

        [[maybe_unused]] [[nodiscard]] double DotProduct(const Quaternion& q) const;

        static Quaternion Euler(const Math::Vector3& euler);
        static Quaternion Euler(float x, float y, float z);
    };

}