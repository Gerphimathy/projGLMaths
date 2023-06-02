//
// Created by Mathis on 20/05/2023.
//

#include <array>
#include <ostream>
#include <cmath>
#include "Matrix.hpp"
#include "Quaternion.hpp"

inline float SIGN(float x) {
    return (x >= 0.0f) ? +1.0f : -1.0f;
}

namespace Math{

    /**
     * |                            |
     * |        Constructors        |
     * |                            |
     */
    Matrix4_4::Matrix4_4() {
        matrix = std::array<std::array<double, 4>, 4>();
        for(int i = 0; i < 4; i++){
            matrix[i] = std::array<double, 4>();
            for(int j = 0; j < 4; j++){
                matrix[i][j] = i == j ? 1 : 0;
            }
        }
    }

    Matrix4_4::Matrix4_4(std::array<std::array<double, 4>, 4> matrix) {
        this->matrix = matrix;
    }

    Matrix4_4::Matrix4_4(Matrix4_4 const &matrix) {
        this->matrix = matrix.getMatrix();
    }



    /**
     * |                                |
     * |        Setters/Getters         |
     * |                                |
     */
    std::array<std::array<double, 4>, 4> Matrix4_4::getMatrix() const {
        return matrix;
    }

    void Matrix4_4::setMatrix(std::array<std::array<double, 4>, 4> m) {
        matrix = m;
    }

    void Matrix4_4::setMatrix(const Matrix4_4& m) {
        matrix = m.getMatrix();
    }

    /**
     * |                                            |
     * |        Row|Lines Setters/Getters           |
     * |                                            |
     */
    std::array<double, 4> Matrix4_4::getLine(int i) const {
        return matrix[i];
    }
    void Matrix4_4::setLine(std::array<double, 4> line, int i) {
        matrix[i] = line;
    }

    std::array<double, 4> Matrix4_4::getColumn(int j) const {
        auto row = std::array<double, 4>();
        for(int i = 0; i < 4; i++){
            row[i] = matrix[i][j];
        }
        return row;
    }
    void Matrix4_4::setColumn(std::array<double, 4> row, int j) {
        for(int i = 0; i < 4; i++){
            matrix[i][j] = row[i];
        }
    }


    /**
     * |                                    |
     * |        Value Setters/Getters       |
     * |                                    |
     */
    void Matrix4_4::set(double value, int i, int j) {
        matrix[i][j] = value;
    }
    double Matrix4_4::get(int i, int j) const {
        return matrix[i][j];
    }

    /**
     * |                        |
     * |        Operators       |
     * |                        |
     */

    Matrix4_4 Matrix4_4::operator+=(const Matrix4_4& m) {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                matrix[i][j] += m.get(i,j);
            }
        }
        return *this;
    }

    Matrix4_4 Matrix4_4::operator+(const Matrix4_4& m) const {
        Matrix4_4 result = *this;
        result += m;
        return result;
    }

    Matrix4_4 Matrix4_4::operator-=(const Matrix4_4& m) {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                matrix[i][j] -= m.get(i,j);
            }
        }
        return *this;
    }

    Matrix4_4 Matrix4_4::operator-(const Matrix4_4& m) const {
        Matrix4_4 result = *this;
        result -= m;
        return result;
    }

    Matrix4_4 Matrix4_4::operator*=(const Matrix4_4& m) {
        Matrix4_4 result;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                double value = 0;
                for(int k = 0; k < 4; k++){
                    value += matrix[i][k] * m.get(k,j);
                }
                result.set(value, i, j);
            }
        }

        return result;
    }

    Matrix4_4 Matrix4_4::operator*(const Matrix4_4& m) const {
        Matrix4_4 result = *this;
        result *= m;
        return result;
    }

    Matrix4_4 Matrix4_4::operator*=(const double& value) {
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                matrix[i][j] *= value;
            }
        }
        return *this;
    }

    Matrix4_4 Matrix4_4::operator*(const double& value) const {
        Matrix4_4 result = *this;
        result *= value;
        return result;
    }

    Matrix4_4& Matrix4_4::operator=(const Matrix4_4& m) {
        matrix = m.getMatrix();
        return *this;
    }

    Matrix4_4& Matrix4_4::operator=(const std::array<float, 16> tab) {
        matrix = Matrix4_4::FromArray(tab).getMatrix();
        return *this;
    }

    bool Matrix4_4::operator==(const Matrix4_4& m) const {
        std::array<std::array<double, 4>,4> other = m.getMatrix();
        //Compare values
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                if(matrix[i][j] != other[i][j]) return false;

        return true;
    }

    bool Matrix4_4::operator!=(const Matrix4_4& m) const {
        return !(*this == m);
    }

    std::ostream& operator<<(std::ostream& os, const Matrix4_4& m) {
        os << "[";
        for(int i = 0; i < 4; i++){
            os << "[";
            for(int j = 0; j < 4; j++){
                os << m.get(i,j);
                if(j != 3) os << ", ";
            }
            os << "]";
            if(i != 3) os << ", ";
        }
        os << "]";
        return os;
    }

    /**
     * |                            |
     * |        Conversion          |
     * |                            |
     */

    Quaternion Matrix4_4::ToQuaternion() const{
        double r11 = get(0, 0);
        double r12 = get(0, 1);
        double r13 = get(0, 2);
        double r21 = get(1, 0);
        double r22 = get(1, 1);
        double r23 = get(1, 2);
        double r31 = get(2, 0);
        double r32 = get(2, 1);
        double r33 = get(2, 2);
        double q0 = (r11 + r22 + r33 + 1.) / 4.;
        double q1 = (r11 - r22 - r33 + 1.) / 4.;
        double q2 = (-r11 + r22 - r33 + 1.) / 4.;
        double q3 = (-r11 - r22 + r33 + 1.) / 4.;
        if (q0 < 0.) {
            q0 = 0.;
        }
        if (q1 < 0.) {
            q1 = 0.;
        }
        if (q2 < 0.) {
            q2 = 0.;
        }
        if (q3 < 0.) {
            q3 = 0.;
        }
        q0 = sqrt(q0);
        q1 = sqrt(q1);
        q2 = sqrt(q2);
        q3 = sqrt(q3);
        if (q0 >= q1 && q0 >= q2 && q0 >= q3) {
            q0 *= +1.;
            q1 *= SIGN(r32 - r23);
            q2 *= SIGN(r13 - r31);
            q3 *= SIGN(r21 - r12);
        } else if (q1 >= q0 && q1 >= q2 && q1 >= q3) {
            q0 *= SIGN(r32 - r23);
            q1 *= +1.;
            q2 *= SIGN(r21 + r12);
            q3 *= SIGN(r13 + r31);
        } else if (q2 >= q0 && q2 >= q1 && q2 >= q3) {
            q0 *= SIGN(r13 - r31);
            q1 *= SIGN(r21 + r12);
            q2 *= +1.;
            q3 *= SIGN(r32 + r23);
        } else if (q3 >= q0 && q3 >= q1 && q3 >= q2) {
            q0 *= SIGN(r21 - r12);
            q1 *= SIGN(r31 + r13);
            q2 *= SIGN(r32 + r23);
            q3 *= +1.;
        } else {
            printf("Should not get there\n");
        }
        double r = Quaternion{q0, q1, q2, q3}.Norm();
        q0 /= r;
        q1 /= r;
        q2 /= r;
        q3 /= r;

        Quaternion q = {q0, q1, q2, q3};
        return q;
    }

    std::array<float, 16> Matrix4_4::ToArray() const {
        std::array<float, 16> temp;
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                temp[4*i+j] = (float)get(j,i);
            }
        }
        return temp;
    }

     Matrix4_4 Matrix4_4::FromArray(std::array<float, 16> tab) {
        Matrix4_4 mat;
        for(int i = 0; i < tab.size(); ++i){
            mat.set(tab[i], i%4, i/4);
        }
        return mat;
    };

    /**
     * |                          |
     * |        Functions         |
     * |                          |
     */



}


