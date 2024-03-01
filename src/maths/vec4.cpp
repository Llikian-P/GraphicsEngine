/******************************************************************************************************
 * @file  vec4.cpp
 * @brief Implementation of the vec4 class
 ******************************************************************************************************/

#include "maths/vec4.hpp"

#include <cmath>
#include <stdexcept>

vec4::vec4() : x{}, y{}, z{}, w{} { }

vec4::vec4(float scalar) : x{scalar}, y{scalar}, z{scalar}, w{scalar} { }

vec4::vec4(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} { }

vec4::vec4(float scalar, float alpha) : x{scalar}, y{scalar}, z{scalar}, w{alpha} { }

float& vec4::operator [](int index) {
    if(index < 0 || index > 3) {
        throw std::out_of_range("Index out of bounds");
    }

    return *(&x + index);
}

void vec4::operator +=(const vec4& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
}

void vec4::operator -=(const vec4& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
}

void vec4::operator *=(const vec4& vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    w *= vec.w;
}

void vec4::operator /=(const vec4& vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    w /= vec.w;
}

void vec4::operator +=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
}

void vec4::operator -=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
}

void vec4::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
}

void vec4::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
}

vec4 operator +(const vec4& v1, const vec4& v2) {
    return vec4{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}

vec4 operator -(const vec4& v1, const vec4& v2) {
    return vec4{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
}

vec4 operator *(const vec4& v1, const vec4& v2) {
    return vec4{v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}

vec4 operator /(const vec4& v1, const vec4& v2) {
    return vec4{v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w};
}

vec4 operator +(const vec4& vec, float scalar) {
    return vec4{vec.x + scalar, vec.y + scalar, vec.z + scalar, vec.w + scalar};
}

vec4 operator -(const vec4& vec, float scalar) {
    return vec4{vec.x - scalar, vec.y - scalar, vec.z - scalar, vec.w - scalar};
}

vec4 operator *(const vec4& vec, float scalar) {
    return vec4{vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar};
}

vec4 operator /(const vec4& vec, float scalar) {
    return vec4{vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar};
}

vec4 operator +(float scalar, const vec4& vec) {
    return vec4{scalar + vec.x, scalar + vec.y, scalar + vec.z, scalar + vec.w};
}

vec4 operator -(float scalar, const vec4& vec) {
    return vec4{scalar - vec.x, scalar - vec.y, scalar - vec.z, scalar - vec.w};
}

vec4 operator *(float scalar, const vec4& vec) {
    return vec4{scalar * vec.x, scalar * vec.y, scalar * vec.z, scalar * vec.w};
}

vec4 operator /(float scalar, const vec4& vec) {
    return vec4{scalar / vec.x, scalar / vec.y, scalar / vec.z, scalar / vec.w};
}

std::istream& operator >>(std::istream& stream, vec4& vec) {
    return stream >> vec.x >> vec.y >> vec.z >> vec.w;
}

std::ostream& operator <<(std::ostream& stream, const vec4& vec) {
    return stream << "( " << vec.x << " ; " << vec.y << " ; " << vec.z << " ; " << vec.w << " )";
}

float length(const vec4& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

vec4 normalize(const vec4& vec) {
    return vec / length(vec);
}

float dot(const vec4& v1, const vec4& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
