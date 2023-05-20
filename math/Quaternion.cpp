#include <array>
#include <ostream>
#include <cmath>
#include "Quaternion.hpp"
#include "Matrix.hpp"

namespace Math{

    /**
    * |                            |
    * |        Constructors        |
    * |                            |
    */

    /**
     * |                                |
     * |        Setters/Getters         |
     * |                                |
     */
    double Quaternion::getS() const {return s;}
    [[maybe_unused]] void Quaternion::setS(double s) {Quaternion::s = s;}

    double Quaternion::getI() const {return i;}
    [[maybe_unused]] void Quaternion::setI(double i) {Quaternion::i = i;}

    double Quaternion::getJ() const {return j;}
    [[maybe_unused]] void Quaternion::setJ(double j) {Quaternion::j = j;}

    double Quaternion::getK() const {return k;}
    [[maybe_unused]] void Quaternion::setK(double k) {Quaternion::k = k;}

    /**
     * |                        |
     * |        Operators       |
     * |                        |
     */

    Quaternion Quaternion::operator+=(const Quaternion& q){
        this->s += q.s;
        this->i += q.i;
        this->j += q.j;
        this->k += q.k;
        return *this;
    }

    Quaternion Quaternion::operator+(const Quaternion& q) const {
        Quaternion result = *this;
        result += q;
        return result;
    }

    Quaternion Quaternion::operator*=(const Quaternion& q){
        this->s = this->s * q.s - this->i * q.i - this->j * q.j - this->k * q.k;
        this->i = this->s * q.i + this->i * q.s + this->j * q.k - this->k * q.j;
        this->j = this->s * q.j + this->j * q.s + this->k * q.i - this->i * q.k;
        this->k = this->s * q.k + this->k * q.s + this->i * q.j - this->j * q.i;
        return *this;
    }

    Quaternion Quaternion::operator*(const Quaternion& q) const {
        Quaternion result = *this;
        result *= q;
        return result;
    }

    Quaternion Quaternion::operator*=(const double &d){
        this->s *= d;
        this->i *= d;
        this->j *= d;
        this->k *= d;
        return *this;
    }

    Quaternion Quaternion::operator*(const double &d) const {
        Quaternion result = *this;
        result *= d;
        return result;
    }

    Quaternion Quaternion::operator^=(const Quaternion &q){
        this->s = 0.0;
        this->i = this->j * q.k - this->k * q.j;
        this->j = this->k * q.i - this->i * q.k;
        this->k = this->i * q.j - this->j * q.i;
        return *this;
    }

    Quaternion Quaternion::operator^(const Quaternion &q) const {
        Quaternion result = *this;
        result ^= q;
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
        os << q.getS() << " + " << q.getI() << "i + " << q.getJ() << "j + " << q.getK() << "k";
        return os;
    }

    Quaternion operator*(const double &d, const Quaternion &q) {
        return q*d;
    }

    /**
     * |                            |
     * |        Conversion          |
     * |                            |
     */

    Matrix4_4 Quaternion::ToMatrix() const{
        std::array<std::array<double, 4>,4> m = std::array<std::array<double, 4>,4>();
        m[0] = { 1 - 2*j*j - 2*k*k, 2*i*j - 2*k*s         , 2*i*k + 2*j*s        , 0.0 };
        m[1] = { 2*i*j + 2*k*s        , 1 - 2*i*i - 2*k*k , 2*j*k -  2*i*s       , 0.0 };
        m[2] = { 2*i*k - 2*j*s        , 2*j*k + 2*i*s         , 1 - 2*i*i - 2*j*j, 0.0 };
        m[3] = {0, 0, 0, 1};
        return Matrix4_4(m);
    }

    /**
     * |                          |
     * |        Functions         |
     * |                          |
     */

    [[maybe_unused]] Quaternion Quaternion::Conjugate() const
    {
        return {s, -i, -j, -k};
    }

    double Quaternion::Norm() const
    {
        return std::sqrt(s*s + i*i + j*j + k*k);
    }

    [[maybe_unused]] Quaternion Quaternion::Normalized() const
    {
        double norm = this->Norm();
        if(norm == 0.0)
        {
            return {};
        }
        return {this->s, this->i / norm, this->j / norm, this->k / norm};
    }

    [[maybe_unused]] double Quaternion::DotProduct(const Quaternion& q) const {
        return this->i*q.i + this->j*q.j + this->k*q.k + this->s*q.s;
    }
}