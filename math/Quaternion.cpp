#include <array>
#include <ostream>
#include <cmath>
#include "Quaternion.hpp"
#include "Matrix.hpp"
#include "Vector3.hpp"

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
        double tempS = s;
        double tempI = i;
        double tempJ = j;
        double tempK = k;
        s = tempS * q.s - tempI * q.i - tempJ * q.j - tempK * q.k;
        i = tempS * q.i + tempI * q.s + tempJ * q.k - tempK * q.j;
        j = tempS * q.j - tempI * q.k + tempJ * q.s + tempK * q.i;
        k = tempS * q.k + tempI * q.j - tempJ * q.i + tempK * q.s;
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

    Quaternion Quaternion::operator*=(const float &d){
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
    Quaternion Quaternion::operator*(const float &d) const {
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
        return q * d;
    }

    Quaternion operator*(const float &d, const Quaternion &q) {
        return q * d;
    }


    Vector3 Quaternion::operator*(const Vector3& v) const {
        /*
        Vector3 u(i, j, k);
        Vector3 t = Vector3::crossProduct(u, v) * (double)2;
        return v + t * s + Vector3::crossProduct(u, t);
         */
        Quaternion vv = {0,v.x,v.y,v.z};
        Quaternion conj = this->Conjugate();
        vv = *this * vv;
        vv *= conj;
        return {vv.i, vv.j, vv.k};
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
        return {this->s / norm, this->i / norm, this->j / norm, this->k / norm};
    }

    Quaternion Quaternion::Normalize(){
        *this = this->Normalized();
        return *this;
    }

    [[maybe_unused]] double Quaternion::DotProduct(const Quaternion& q) const {
        return this->i*q.i + this->j*q.j + this->k*q.k + this->s*q.s;
    }

    Quaternion Quaternion::Euler(const Math::Vector3& euler) {
        return Quaternion::Euler(euler.x, euler.y, euler.z);
    }

    Quaternion Quaternion::Euler(double x, double y, double z) {
        float cos1 = cos(x / 2);
        float cos2 = cos(y / 2);
        float cos3 = cos(z / 2);
        float sin1 = sin(x / 2);
        float sin2 = sin(y / 2);
        float sin3 = sin(z / 2);

        return Quaternion(
                cos1 * cos2 * cos3 - sin1 * sin2 * sin3,
                sin1 * cos2 * cos3 + cos1 * sin2 * sin3,
                cos1 * sin2 * cos3 + sin1 * cos2 * sin3,
                cos1 * cos2 * sin3 - sin1 * sin2 * cos3
        );
    }

    Vector3 Quaternion::toEuler() const {
        double square_s = s * s;
        double square_i = i * i;
        double square_j = j * j;
        double square_k = k * k;
        double unit = square_i + square_j + square_k + square_s;
        double test = i * j + k * s;

        Vector3 euler;

        if (test > 0.4999 * unit) {
            euler.y = 2 * atan2(i, s);
            euler.z = M_PI / 2;
            euler.x = 0;
            return euler;
        }

        if (test < -0.4999 * unit) {
            euler.y = -2 * atan2(i, s);
            euler.z = -M_PI / 2;
            euler.x = 0;
            return euler;
        }

        euler.y = atan2(2 * j * s - 2 * i * k, square_i - square_j - square_k + square_s);
        euler.z = asin(2 * test / unit);
        euler.x = atan2(2 * i * s - 2 * j * k, -square_i + square_j - square_k + square_s);

        return euler;
    }
}