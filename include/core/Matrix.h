#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

#include "Essential.h"
#include <ostream>

namespace core {

/**
 * Template Matrix class to represent rowsxcols matrices
 *
 * @details Matrices are row-major
 * @tparam rows - int amount of rows in matrix
 * @tparam cols - int amount of columns in matrix
 * @tparam T - type of elements of the matrix
 */
template<int rows, int cols, typename T> class Matrix {
protected:
    T data[rows][cols];
};

/**
 * 3x3 matrix of float
 * @details Matrix is row-major
 */
template<> class Matrix<3, 3, float> {
public:
    Matrix(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22 )
    {
        data[0][0] = m00; data[0][1] = m01; data[0][2] = m02;
        data[1][0] = m10; data[1][1] = m11; data[1][2] = m12;
        data[2][0] = m20; data[2][1] = m21; data[2][2] = m22;
    }

    const float* operator[] (int row) const {
        return data[row];
    }
    float* operator[] (int row) {
        return data[row];
    }

    static const Matrix3 zero;
    static const Matrix3 identity;

protected:
    float data[3][3];

};

/**
 * 4x4 matrix of float
 * @details Matrix is row-major
 */
template<> class Matrix<4, 4, float> {
public:
    Matrix() {}
    Matrix(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33 )
    {
        data[0][0] = m00; data[0][1] = m01; data[0][2] = m02; data[0][3] = m03;
        data[1][0] = m10; data[1][1] = m11; data[1][2] = m12; data[1][3] = m13;
        data[2][0] = m20; data[2][1] = m21; data[2][2] = m22; data[2][3] = m23;
        data[3][0] = m30; data[3][1] = m31; data[3][2] = m32; data[3][3] = m33;
    }

    const float* operator[] (int row) const {
        return data[row];
    }
    float* operator[] (int row) {
        return data[row];
    }

    /**
     * @return pointer to first element of the matrix
     */
    float* GetPtr() {
        return &data[0][0];
    }

    static const Matrix4 zero;
    static const Matrix4 identity;

    float data[4][4];

};

Matrix4 operator*(const Matrix4 &lhs, const Matrix4 &rhs);

inline std::ostream& operator<<(std::ostream& o, const Matrix4 &mat)
{
    o << "Matrix4x4(" << std::endl;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            o << mat[i][j];
            if(j != 3)
                o << ", ";
        }

        if(i != 3)
            o << "; ";
    }
    o << ")";
    return o;
}

} // namespace core

#endif //CORE_MATRIX_H
