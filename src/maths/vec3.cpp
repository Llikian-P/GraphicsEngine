/******************************************************************************************************
 * @file  vec3.cpp
 * @brief Implementation of the vec3 class
 ******************************************************************************************************/

#include "maths/vec3.hpp"

#include <cmath>
#include <stdexcept>

vec3::vec3() : x{}, y{}, z{} { }

vec3::vec3(float scalar) : x{scalar}, y{scalar}, z{scalar} { }

vec3::vec3(float x, float y, float z) : x{x}, y{y}, z{z} { }

float& vec3::operator [](int index) {
    if(index < 0 || index > 2) {
        throw std::out_of_range("Index out of bounds");
    }

    return *(&x + index);
}

void vec3::operator +=(const vec3& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
}

void vec3::operator -=(const vec3& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
}

void vec3::operator *=(const vec3& vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
}

void vec3::operator /=(const vec3& vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
}

void vec3::operator +=(float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
}

void vec3::operator -=(float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
}

void vec3::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void vec3::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

vec3 operator +(const vec3& v1, const vec3& v2) {
    return vec3{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

vec3 operator -(const vec3& v1, const vec3& v2) {
    return vec3{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

vec3 operator *(const vec3& v1, const vec3& v2) {
    return vec3{v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

vec3 operator /(const vec3& v1, const vec3& v2) {
    return vec3{v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

vec3 operator +(const vec3& vec, float scalar) {
    return vec3{vec.x + scalar, vec.y + scalar, vec.z + scalar};
}

vec3 operator -(const vec3& vec, float scalar) {
    return vec3{vec.x - scalar, vec.y - scalar, vec.z - scalar};
}

vec3 operator *(const vec3& vec, float scalar) {
    return vec3{vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

vec3 operator /(const vec3& vec, float scalar) {
    return vec3{vec.x / scalar, vec.y / scalar, vec.z / scalar};
}

vec3 operator +(float scalar, const vec3& vec) {
    return vec3{scalar + vec.x, scalar + vec.y, scalar + vec.z};
}

vec3 operator -(float scalar, const vec3& vec) {
    return vec3{scalar - vec.x, scalar - vec.y, scalar - vec.z};
}

vec3 operator *(float scalar, const vec3& vec) {
    return vec3{scalar * vec.x, scalar * vec.y, scalar * vec.z};
}

vec3 operator /(float scalar, const vec3& vec) {
    return vec3{scalar / vec.x, scalar / vec.y, scalar / vec.z};
}

std::istream& operator >>(std::istream& stream, vec3& vec) {
    return stream >> vec.x >> vec.y >> vec.z;
}

std::ostream& operator <<(std::ostream& stream, const vec3& vec) {
    return stream << "( " << vec.x << " ; " << vec.y << " ; " << vec.z << " )";
}

float length(const vec3& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

vec3 normalize(const vec3& vec) {
    return vec / length(vec);
}

float dot(const vec3& v1, const vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}
