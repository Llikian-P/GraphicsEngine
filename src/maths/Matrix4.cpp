/******************************************************************************************************
 * @file  Matrix4.cpp
 * @brief Implementation of the Matrix4 class
 ******************************************************************************************************/

#include "maths/Matrix4.hpp"

#include <stdexcept>

Matrix4::Matrix4()
    : values{1.0f, 0.0f, 0.0f, 0.0f,
             0.0f, 1.0f, 0.0f, 0.0f,
             0.0f, 0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f} { }

Matrix4::Matrix4(float scalar)
    : values{scalar, 0.0f, 0.0f, 0.0f,
             0.0f, scalar, 0.0f, 0.0f,
             0.0f, 0.0f, scalar, 0.0f,
             0.0f, 0.0f, 0.0f, scalar} { }

Matrix4::Matrix4(float M00, float M01, float M02, float M03,
                 float M10, float M11, float M12, float M13,
                 float M20, float M21, float M22, float M23,
                 float M30, float M31, float M32, float M33)
    : values{M00, M01, M02, M03,
             M10, M11, M12, M13,
             M20, M21, M22, M23,
             M30, M31, M32, M33} { }

Matrix4::Matrix4(float M00, float M01, float M02, float M10, float M11, float M12, float M20, float M21, float M22)
    : values{M00, M01, M02, 0.0f,
             M10, M11, M12, 0.0f,
             M20, M21, M22, 0.0f,
             0.0f, 0.0f, 0.0f, 1.0f} { }

Matrix4::Matrix4(float M00, float M11, float M22, float M33)
    : values{M00, 0.0f, 0.0f, 0.0f,
             0.0f, M11, 0.0f, 0.0f,
             0.0f, 0.0f, M22, 0.0f,
             0.0f, 0.0f, 0.0f, M33} { }

float& Matrix4::operator ()(int row, int column) {
    if(row < 0 || row > 3 || column < 0 || column > 3) {
        throw std::out_of_range("Index out of bounds");
    }

    return values[row][column];
}

const float* Matrix4::operator [](int row) const {
    if(row < 0 || row > 3) {
        throw std::out_of_range("Index out of bounds");
    }

    return values[row];
}

void Matrix4::operator +=(const Matrix4& mat) {
    values[0][0] += mat[0][0];
    values[0][1] += mat[0][1];
    values[0][2] += mat[0][2];
    values[0][3] += mat[0][3];

    values[1][0] += mat[1][0];
    values[1][1] += mat[1][1];
    values[1][2] += mat[1][2];
    values[1][3] += mat[1][3];

    values[2][0] += mat[2][0];
    values[2][1] += mat[2][1];
    values[2][2] += mat[2][2];
    values[2][3] += mat[2][3];

    values[3][0] += mat[3][0];
    values[3][1] += mat[3][1];
    values[3][2] += mat[3][2];
    values[3][3] += mat[3][3];
}

void Matrix4::operator -=(const Matrix4& mat) {
    values[0][0] -= mat[0][0];
    values[0][1] -= mat[0][1];
    values[0][2] -= mat[0][2];
    values[0][3] -= mat[0][3];

    values[1][0] -= mat[1][0];
    values[1][1] -= mat[1][1];
    values[1][2] -= mat[1][2];
    values[1][3] -= mat[1][3];

    values[2][0] -= mat[2][0];
    values[2][1] -= mat[2][1];
    values[2][2] -= mat[2][2];
    values[2][3] -= mat[2][3];

    values[3][0] -= mat[3][0];
    values[3][1] -= mat[3][1];
    values[3][2] -= mat[3][2];
    values[3][3] -= mat[3][3];
}

void Matrix4::operator *=(const Matrix4& mat) {
    values[0][0] = values[0][0] * mat[0][0] + values[0][1] * mat[1][0] + values[0][2] * mat[2][0] + values[0][3] * mat[3][0];
    values[0][1] = values[0][0] * mat[0][1] + values[0][1] * mat[1][1] + values[0][2] * mat[2][1] + values[0][3] * mat[3][1];
    values[0][2] = values[0][0] * mat[0][2] + values[0][1] * mat[1][2] + values[0][2] * mat[2][2] + values[0][3] * mat[3][2];
    values[0][3] = values[0][0] * mat[0][3] + values[0][1] * mat[1][3] + values[0][2] * mat[2][3] + values[0][3] * mat[3][3];

    values[1][0] = values[1][0] * mat[0][0] + values[1][1] * mat[1][0] + values[1][2] * mat[2][0] + values[1][3] * mat[3][0];
    values[1][1] = values[1][0] * mat[0][1] + values[1][1] * mat[1][1] + values[1][2] * mat[2][1] + values[1][3] * mat[3][1];
    values[1][2] = values[1][0] * mat[0][2] + values[1][1] * mat[1][2] + values[1][2] * mat[2][2] + values[1][3] * mat[3][2];
    values[1][3] = values[1][0] * mat[0][3] + values[1][1] * mat[1][3] + values[1][2] * mat[2][3] + values[1][3] * mat[3][3];

    values[2][0] = values[2][0] * mat[0][0] + values[2][1] * mat[1][0] + values[2][2] * mat[2][0] + values[2][3] * mat[3][0];
    values[2][1] = values[2][0] * mat[0][1] + values[2][1] * mat[1][1] + values[2][2] * mat[2][1] + values[2][3] * mat[3][1];
    values[2][2] = values[2][0] * mat[0][2] + values[2][1] * mat[1][2] + values[2][2] * mat[2][2] + values[2][3] * mat[3][2];
    values[2][3] = values[2][0] * mat[0][3] + values[2][1] * mat[1][3] + values[2][2] * mat[2][3] + values[2][3] * mat[3][3];

    values[2][0] = values[3][0] * mat[0][0] + values[3][1] * mat[1][0] + values[3][2] * mat[2][0] + values[3][3] * mat[3][0];
    values[2][1] = values[3][0] * mat[0][1] + values[3][1] * mat[1][1] + values[3][2] * mat[2][1] + values[3][3] * mat[3][1];
    values[2][2] = values[3][0] * mat[0][2] + values[3][1] * mat[1][2] + values[3][2] * mat[2][2] + values[3][3] * mat[3][2];
    values[2][3] = values[3][0] * mat[0][3] + values[3][1] * mat[1][3] + values[3][2] * mat[2][3] + values[3][3] * mat[3][3];
}

void Matrix4::operator +=(float scalar) {
    values[0][0] += scalar;
    values[0][1] += scalar;
    values[0][2] += scalar;
    values[0][3] += scalar;

    values[1][0] += scalar;
    values[1][1] += scalar;
    values[1][2] += scalar;
    values[1][3] += scalar;

    values[2][0] += scalar;
    values[2][1] += scalar;
    values[2][2] += scalar;
    values[2][3] += scalar;

    values[3][0] += scalar;
    values[3][1] += scalar;
    values[3][2] += scalar;
    values[3][3] += scalar;
}

void Matrix4::operator -=(float scalar) {
    values[0][0] -= scalar;
    values[0][1] -= scalar;
    values[0][2] -= scalar;
    values[0][3] -= scalar;

    values[1][0] -= scalar;
    values[1][1] -= scalar;
    values[1][2] -= scalar;
    values[1][3] -= scalar;

    values[2][0] -= scalar;
    values[2][1] -= scalar;
    values[2][2] -= scalar;
    values[2][3] -= scalar;

    values[3][0] -= scalar;
    values[3][1] -= scalar;
    values[3][2] -= scalar;
    values[3][3] -= scalar;
}

void Matrix4::operator *=(float scalar) {
    values[0][0] *= scalar;
    values[0][1] *= scalar;
    values[0][2] *= scalar;
    values[0][3] *= scalar;

    values[1][0] *= scalar;
    values[1][1] *= scalar;
    values[1][2] *= scalar;
    values[1][3] *= scalar;

    values[2][0] *= scalar;
    values[2][1] *= scalar;
    values[2][2] *= scalar;
    values[2][3] *= scalar;

    values[3][0] *= scalar;
    values[3][1] *= scalar;
    values[3][2] *= scalar;
    values[3][3] *= scalar;
}

void Matrix4::operator /=(float scalar) {
    values[0][0] /= scalar;
    values[0][1] /= scalar;
    values[0][2] /= scalar;
    values[0][3] /= scalar;

    values[1][0] /= scalar;
    values[1][1] /= scalar;
    values[1][2] /= scalar;
    values[1][3] /= scalar;

    values[2][0] /= scalar;
    values[2][1] /= scalar;
    values[2][2] /= scalar;
    values[2][3] /= scalar;

    values[3][0] /= scalar;
    values[3][1] /= scalar;
    values[3][2] /= scalar;
    values[3][3] /= scalar;
}

Matrix4 operator +(const Matrix4& mat1, const Matrix4& mat2) {
    return Matrix4{mat1[0][0] + mat2[0][0], mat1[0][1] + mat2[0][1], mat1[0][2] + mat2[0][2], mat1[0][3] + mat2[0][3],
                   mat1[1][0] + mat2[1][0], mat1[1][1] + mat2[1][1], mat1[1][2] + mat2[1][2], mat1[1][3] + mat2[1][3],
                   mat1[2][0] + mat2[2][0], mat1[2][1] + mat2[2][1], mat1[2][2] + mat2[2][2], mat1[2][3] + mat2[2][3],
                   mat1[3][0] + mat2[3][0], mat1[3][1] + mat2[3][1], mat1[3][2] + mat2[3][2], mat1[3][3] + mat2[3][3]};
}

Matrix4 operator -(const Matrix4& mat1, const Matrix4& mat2) {
    return Matrix4{mat1[0][0] - mat2[0][0], mat1[0][1] - mat2[0][1], mat1[0][2] - mat2[0][2], mat1[0][3] - mat2[0][3],
                   mat1[1][0] - mat2[1][0], mat1[1][1] - mat2[1][1], mat1[1][2] - mat2[1][2], mat1[1][3] - mat2[1][3],
                   mat1[2][0] - mat2[2][0], mat1[2][1] - mat2[2][1], mat1[2][2] - mat2[2][2], mat1[2][3] - mat2[2][3],
                   mat1[3][0] - mat2[3][0], mat1[3][1] - mat2[3][1], mat1[3][2] - mat2[3][2], mat1[3][3] - mat2[3][3]};
}

Matrix4 operator *(const Matrix4& mat1, const Matrix4& mat2) {
    return Matrix4{mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0] + mat1[0][2] * mat2[2][0] + mat1[0][3] * mat2[3][0],
                   mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1] + mat1[0][2] * mat2[2][1] + mat1[0][3] * mat2[3][1],
                   mat1[0][0] * mat2[0][2] + mat1[0][1] * mat2[1][2] + mat1[0][2] * mat2[2][2] + mat1[0][3] * mat2[3][2],
                   mat1[0][0] * mat2[0][3] + mat1[0][1] * mat2[1][3] + mat1[0][2] * mat2[2][3] + mat1[0][3] * mat2[3][3],

                   mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0] + mat1[1][2] * mat2[2][0] + mat1[1][3] * mat2[3][0],
                   mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1] + mat1[1][2] * mat2[2][1] + mat1[1][3] * mat2[3][1],
                   mat1[1][0] * mat2[0][2] + mat1[1][1] * mat2[1][2] + mat1[1][2] * mat2[2][2] + mat1[1][3] * mat2[3][2],
                   mat1[1][0] * mat2[0][3] + mat1[1][1] * mat2[1][3] + mat1[1][2] * mat2[2][3] + mat1[1][3] * mat2[3][3],

                   mat1[2][0] * mat2[0][0] + mat1[2][1] * mat2[1][0] + mat1[2][2] * mat2[2][0] + mat1[2][3] * mat2[3][0],
                   mat1[2][0] * mat2[0][1] + mat1[2][1] * mat2[1][1] + mat1[2][2] * mat2[2][1] + mat1[2][3] * mat2[3][1],
                   mat1[2][0] * mat2[0][2] + mat1[2][1] * mat2[1][2] + mat1[2][2] * mat2[2][2] + mat1[2][3] * mat2[3][2],
                   mat1[2][0] * mat2[0][3] + mat1[2][1] * mat2[1][3] + mat1[2][2] * mat2[2][3] + mat1[2][3] * mat2[3][3],

                   mat1[3][0] * mat2[0][0] + mat1[3][1] * mat2[1][0] + mat1[3][2] * mat2[2][0] + mat1[3][3] * mat2[3][0],
                   mat1[3][0] * mat2[0][1] + mat1[3][1] * mat2[1][1] + mat1[3][2] * mat2[2][1] + mat1[3][3] * mat2[3][1],
                   mat1[3][0] * mat2[0][2] + mat1[3][1] * mat2[1][2] + mat1[3][2] * mat2[2][2] + mat1[3][3] * mat2[3][2],
                   mat1[3][0] * mat2[0][3] + mat1[3][1] * mat2[1][3] + mat1[3][2] * mat2[2][3] + mat1[3][3] * mat2[3][3]};
}

Matrix4 operator +(const Matrix4& mat, float scalar) {
    return Matrix4{mat[0][0] + scalar, mat[0][1] + scalar, mat[0][2] + scalar, mat[0][3] + scalar,
                   mat[1][0] + scalar, mat[1][1] + scalar, mat[1][2] + scalar, mat[1][3] + scalar,
                   mat[2][0] + scalar, mat[2][1] + scalar, mat[2][2] + scalar, mat[2][3] + scalar,
                   mat[3][0] + scalar, mat[3][1] + scalar, mat[3][2] + scalar, mat[3][3] + scalar};
}

Matrix4 operator -(const Matrix4& mat, float scalar) {
    return Matrix4{mat[0][0] - scalar, mat[0][1] - scalar, mat[0][2] - scalar, mat[0][3] - scalar,
                   mat[1][0] - scalar, mat[1][1] - scalar, mat[1][2] - scalar, mat[1][3] - scalar,
                   mat[2][0] - scalar, mat[2][1] - scalar, mat[2][2] - scalar, mat[2][3] - scalar,
                   mat[3][0] - scalar, mat[3][1] - scalar, mat[3][2] - scalar, mat[3][3] - scalar};
}

Matrix4 operator *(const Matrix4& mat, float scalar) {
    return Matrix4{mat[0][0] * scalar, mat[0][1] * scalar, mat[0][2] * scalar, mat[0][3] * scalar,
                   mat[1][0] * scalar, mat[1][1] * scalar, mat[1][2] * scalar, mat[1][3] * scalar,
                   mat[2][0] * scalar, mat[2][1] * scalar, mat[2][2] * scalar, mat[2][3] * scalar,
                   mat[3][0] * scalar, mat[3][1] * scalar, mat[3][2] * scalar, mat[3][3] * scalar};
}

Matrix4 operator /(const Matrix4& mat, float scalar) {
    return Matrix4{mat[0][0] / scalar, mat[0][1] / scalar, mat[0][2] / scalar, mat[0][3] / scalar,
                   mat[1][0] / scalar, mat[1][1] / scalar, mat[1][2] / scalar, mat[1][3] / scalar,
                   mat[2][0] / scalar, mat[2][1] / scalar, mat[2][2] / scalar, mat[2][3] / scalar,
                   mat[3][0] / scalar, mat[3][1] / scalar, mat[3][2] / scalar, mat[3][3] / scalar};
}

Matrix4 operator +(float scalar, const Matrix4& mat) {
    return Matrix4{scalar + mat[0][0], scalar + mat[0][1], scalar + mat[0][2], scalar + mat[0][3],
                   scalar + mat[1][0], scalar + mat[1][1], scalar + mat[1][2], scalar + mat[1][3],
                   scalar + mat[2][0], scalar + mat[2][1], scalar + mat[2][2], scalar + mat[2][3],
                   scalar + mat[3][0], scalar + mat[3][1], scalar + mat[3][2], scalar + mat[3][3]};
}

Matrix4 operator -(float scalar, const Matrix4& mat) {
    return Matrix4{scalar - mat[0][0], scalar - mat[0][1], scalar - mat[0][2], scalar - mat[0][3],
                   scalar - mat[1][0], scalar - mat[1][1], scalar - mat[1][2], scalar - mat[1][3],
                   scalar - mat[2][0], scalar - mat[2][1], scalar - mat[2][2], scalar - mat[2][3],
                   scalar - mat[3][0], scalar - mat[3][1], scalar - mat[3][2], scalar - mat[3][3]};
}

Matrix4 operator *(float scalar, const Matrix4& mat) {
    return Matrix4{scalar * mat[0][0], scalar * mat[0][1], scalar * mat[0][2], scalar * mat[0][3],
                   scalar * mat[1][0], scalar * mat[1][1], scalar * mat[1][2], scalar * mat[1][3],
                   scalar * mat[2][0], scalar * mat[2][1], scalar * mat[2][2], scalar * mat[2][3],
                   scalar * mat[3][0], scalar * mat[3][1], scalar * mat[3][2], scalar * mat[3][3]};
}

Matrix4 operator /(float scalar, const Matrix4& mat) {
    return Matrix4{scalar / mat[0][0], scalar / mat[0][1], scalar / mat[0][2], scalar / mat[0][3],
                   scalar / mat[1][0], scalar / mat[1][1], scalar / mat[1][2], scalar / mat[1][3],
                   scalar / mat[2][0], scalar / mat[2][1], scalar / mat[2][2], scalar / mat[2][3],
                   scalar / mat[3][0], scalar / mat[3][1], scalar / mat[3][2], scalar + mat[3][3]};
}

vec3 operator *(const Matrix4& mat, const vec3& vec) {
    return vec3{mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z + mat[0][3],
                mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z + mat[1][3],
                mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z + mat[2][3]};
}

vec4 operator *(const Matrix4& mat, const vec4& vec) {
    return vec4{mat[0][0] * vec.x + mat[0][1] * vec.y + mat[0][2] * vec.z + mat[0][3] * vec.w,
                mat[1][0] * vec.x + mat[1][1] * vec.y + mat[1][2] * vec.z + mat[1][3] * vec.w,
                mat[2][0] * vec.x + mat[2][1] * vec.y + mat[2][2] * vec.z + mat[2][3] * vec.w,
                mat[3][0] * vec.x + mat[3][1] * vec.y + mat[3][2] * vec.z + mat[3][3] * vec.w};
}

std::istream& operator >>(std::istream& stream, Matrix4& mat) {
    stream >> mat(0, 0) >> mat(0, 1) >> mat(0, 2) >> mat(0, 3);
    stream >> mat(1, 0) >> mat(1, 1) >> mat(1, 2) >> mat(1, 3);
    stream >> mat(2, 0) >> mat(2, 1) >> mat(2, 2) >> mat(2, 3);
    stream >> mat(3, 0) >> mat(3, 1) >> mat(3, 2) >> mat(3, 3);

    return stream;
}

std::ostream& operator <<(std::ostream& stream, const Matrix4& mat) {
    stream << "( " << mat[0][0] << " ; " << mat[0][1] << " ; " << mat[0][2] << " ; " << mat[0][3] << " )\n";
    stream << "( " << mat[1][0] << " ; " << mat[1][1] << " ; " << mat[1][2] << " ; " << mat[1][3] << " )\n";
    stream << "( " << mat[2][0] << " ; " << mat[2][1] << " ; " << mat[2][2] << " ; " << mat[2][3] << " )\n";
    stream << "( " << mat[3][0] << " ; " << mat[3][1] << " ; " << mat[3][2] << " ; " << mat[3][3] << " )";

    return stream;
}

float determinant(const Matrix4& mat) {
    float a = mat[1][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3])
              - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3])
              + mat[1][3] * (mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2]);

    float b = mat[1][0] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3])
              - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3])
              + mat[1][3] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]);

    float c = mat[1][0] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3])
              - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3])
              + mat[1][3] * (mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]);

    float d = mat[1][0] * (mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2])
              - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2])
              + mat[1][2] * (mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]);

    return mat[0][0] * a - mat[0][1] * b + mat[0][2] * c - mat[0][3] * d;
}

Matrix4 transpose(const Matrix4& mat) {
    return Matrix4{mat[0][0], mat[1][0], mat[2][0], mat[3][0],
                   mat[0][1], mat[1][1], mat[2][1], mat[3][1],
                   mat[0][2], mat[1][2], mat[2][2], mat[3][2],
                   mat[0][3], mat[1][3], mat[2][3], mat[3][3]};
}

Matrix4 inverse(const Matrix4& mat) {
    float a = mat[1][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3])
              - mat[1][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3])
              + mat[1][3] * (mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2]);

    float b = mat[1][0] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3])
              - mat[1][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3])
              + mat[1][3] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]);

    float c = mat[1][0] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3])
              - mat[1][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3])
              + mat[1][3] * (mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]);

    float d = mat[1][0] * (mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2])
              - mat[1][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2])
              + mat[1][2] * (mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]);

    float det = mat[0][0] * a - mat[0][1] * b + mat[0][2] * c - mat[0][3] * d;

    if(det == 0) {
        return Matrix4{};
    }

    Matrix4 inv;

    inv(0, 0) = a;

    inv(0, 1) = -(mat[0][1] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3])
                  - mat[0][2] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3])
                  + mat[0][3] * (mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2]));

    inv(0, 2) = mat[0][1] * (mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3])
                - mat[0][2] * (mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3])
                + mat[0][3] * (mat[1][1] * mat[3][2] - mat[3][1] * mat[1][2]);

    inv(0, 3) = -(mat[0][1] * (mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3])
                  - mat[0][2] * (mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3])
                  + mat[0][3] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]));

    inv(1, 0) = -b;

    inv(1, 1) = mat[0][0] * (mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3])
                - mat[0][2] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3])
                + mat[0][3] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]);

    inv(1, 2) = -(mat[0][0] * (mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3])
                  - mat[0][2] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3])
                  + mat[0][3] * (mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2]));

    inv(1, 3) = mat[0][0] * (mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3])
                - mat[0][2] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3])
                + mat[0][3] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);

    inv(2, 0) = c;

    inv(2, 1) = -(mat[0][0] * (mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3])
                  - mat[0][1] * (mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3])
                  + mat[0][3] * (mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]));

    inv(2, 2) = mat[0][0] * (mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3])
                - mat[0][1] * (mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3])
                + mat[0][3] * (mat[1][0] * mat[3][1] - mat[3][0] * mat[1][1]);

    inv(2, 3) = -(mat[0][0] * (mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3])
                  - mat[0][1] * (mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3])
                  + mat[0][3] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]));

    inv(3, 0) = -d;

    inv(3, 1) = mat[0][0] * (mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2])
                - mat[0][1] * (mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2])
                + mat[0][2] * (mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]);

    inv(3, 2) = -(mat[0][0] * (mat[1][1] * mat[3][2] - mat[3][1] * mat[1][2])
                  - mat[0][1] * (mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2])
                  + mat[0][2] * (mat[1][0] * mat[3][1] - mat[3][0] * mat[1][1]));

    inv(3, 3) = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
                - mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2])
                + mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);

    return inv / det;
}