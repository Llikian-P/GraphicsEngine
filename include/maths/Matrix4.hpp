/******************************************************************************************************
 * @file  Matrix4.cpp
 * @brief Declaration of the Matrix4 class
 ******************************************************************************************************/

#pragma once

#include <istream>
#include <ostream>

#include "maths/vec3.hpp"
#include "maths/vec4.hpp"

class Matrix4 {
public:
    Matrix4();
    explicit Matrix4(float scalar);

    explicit Matrix4(float M00, float M01, float M02, float M03,
                     float M10, float M11, float M12, float M13,
                     float M20, float M21, float M22, float M23,
                     float M30, float M31, float M32, float M33);

    explicit Matrix4(float M00, float M01, float M02,
                     float M10, float M11, float M12,
                     float M20, float M21, float M22);

    explicit Matrix4(float M00, float M11, float M22, float M33);

    float& operator ()(int, int);
    const float* operator [](int) const;

    void operator +=(const Matrix4& mat);
    void operator -=(const Matrix4& mat);
    void operator *=(const Matrix4& mat);

    void operator +=(float scalar);
    void operator -=(float scalar);
    void operator *=(float scalar);
    void operator /=(float scalar);

    float values[4][4];
};

Matrix4 operator +(const Matrix4& mat1, const Matrix4& mat2);
Matrix4 operator -(const Matrix4& mat1, const Matrix4& mat2);
Matrix4 operator *(const Matrix4& mat1, const Matrix4& mat2);

Matrix4 operator +(const Matrix4& mat, float scalar);
Matrix4 operator -(const Matrix4& mat, float scalar);
Matrix4 operator *(const Matrix4& mat, float scalar);
Matrix4 operator /(const Matrix4& mat, float scalar);

Matrix4 operator +(float scalar, const Matrix4& mat);
Matrix4 operator -(float scalar, const Matrix4& mat);
Matrix4 operator *(float scalar, const Matrix4& mat);
Matrix4 operator /(float scalar, const Matrix4& mat);

vec3 operator *(const Matrix4& mat, const vec3& vec);
vec4 operator *(const Matrix4& mat, const vec4& vec);

std::istream& operator >>(std::istream& stream, Matrix4& mat);
std::ostream& operator <<(std::ostream& stream, const Matrix4& mat);


float determinant(const Matrix4& mat);

Matrix4 transpose(const Matrix4& mat);
Matrix4 inverse(const Matrix4& mat);