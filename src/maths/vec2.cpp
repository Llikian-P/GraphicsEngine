/******************************************************************************************************
 * @file  vec2.cpp
 * @brief Implementation of the vec2 class
 ******************************************************************************************************/

#include "maths/vec2.hpp"

#include <cmath>
#include <stdexcept>

vec2::vec2() : x{}, y{} { }

vec2::vec2(float scalar) : x{scalar}, y{scalar} { }

vec2::vec2(float x, float y) : x{x}, y{y} { }

float& vec2::operator [](int index) {
    if(index < 0 || index > 1) {
        throw std::out_of_range("Index out of bounds");
    }

    return *(&x + index);
}

void vec2::operator +=(const vec2& vec) {
    x += vec.x;
    y += vec.y;
}

void vec2::operator -=(const vec2& vec) {
    x -= vec.x;
    y -= vec.y;
}

void vec2::operator *=(const vec2& vec) {
    x *= vec.x;
    y *= vec.y;
}

void vec2::operator /=(const vec2& vec) {
    x /= vec.x;
    y /= vec.y;
}

void vec2::operator +=(float scalar) {
    x += scalar;
    y += scalar;
}

void vec2::operator -=(float scalar) {
    x -= scalar;
    y -= scalar;
}

void vec2::operator *=(float scalar) {
    x *= scalar;
    y *= scalar;
}

void vec2::operator /=(float scalar) {
    x /= scalar;
    y /= scalar;
}

vec2 operator +(const vec2& v1, const vec2& v2) {
    return vec2{v1.x + v2.x, v1.y + v2.y};
}

vec2 operator -(const vec2& v1, const vec2& v2) {
    return vec2{v1.x - v2.x, v1.y - v2.y};
}

vec2 operator *(const vec2& v1, const vec2& v2) {
    return vec2{v1.x * v2.x, v1.y * v2.y};
}

vec2 operator /(const vec2& v1, const vec2& v2) {
    return vec2{v1.x / v2.x, v1.y / v2.y};
}

vec2 operator +(const vec2& vec, float scalar) {
    return vec2{vec.x + scalar, vec.y + scalar};
}

vec2 operator -(const vec2& vec, float scalar) {
    return vec2{vec.x - scalar, vec.y - scalar};
}

vec2 operator *(const vec2& vec, float scalar) {
    return vec2{vec.x * scalar, vec.y * scalar};
}

vec2 operator /(const vec2& vec, float scalar) {
    return vec2{vec.x / scalar, vec.y / scalar};
}

vec2 operator +(float scalar, const vec2& vec) {
    return vec2{scalar + vec.x, scalar + vec.y};
}

vec2 operator -(float scalar, const vec2& vec) {
    return vec2{scalar - vec.x, scalar - vec.y};
}

vec2 operator *(float scalar, const vec2& vec) {
    return vec2{scalar * vec.x, scalar * vec.y};
}

vec2 operator /(float scalar, const vec2& vec) {
    return vec2{scalar / vec.x, scalar / vec.y};
}

std::istream& operator >>(std::istream& stream, vec2& vec) {
    return stream >> vec.x >> vec.y;
}

std::ostream& operator <<(std::ostream& stream, const vec2& vec) {
    return stream << "( " << vec.x << " ; " << vec.y << " )";
}

float length(const vec2& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

vec2 normalize(const vec2& vec) {
    return vec / length(vec);
}

float dot(const vec2& v1, const vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
