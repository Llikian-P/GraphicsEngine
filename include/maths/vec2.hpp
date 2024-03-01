/******************************************************************************************************
 * @file  vec2.cpp
 * @brief Declaration of the vec2 class
 ******************************************************************************************************/

#pragma once

#include <istream>
#include <ostream>

class vec2 {
public:
    vec2();
    vec2(float scalar);
    vec2(float x, float y);
    vec2& operator =(const vec2&) = default;

    float& operator [](int index);

    void operator +=(const vec2& vec);
    void operator -=(const vec2& vec);
    void operator *=(const vec2& vec);
    void operator /=(const vec2& vec);

    void operator +=(float scalar);
    void operator -=(float scalar);
    void operator *=(float scalar);
    void operator /=(float scalar);

    float x, y;
};

using Point2D = vec2;
using TexCoord = vec2;

vec2 operator +(const vec2& v1, const vec2& v2);
vec2 operator -(const vec2& v1, const vec2& v2);
vec2 operator *(const vec2& v1, const vec2& v2);
vec2 operator /(const vec2& v1, const vec2& v2);

vec2 operator +(const vec2& vec, float scalar);
vec2 operator -(const vec2& vec, float scalar);
vec2 operator *(const vec2& vec, float scalar);
vec2 operator /(const vec2& vec, float scalar);

vec2 operator +(float scalar, const vec2& vec);
vec2 operator -(float scalar, const vec2& vec);
vec2 operator *(float scalar, const vec2& vec);
vec2 operator /(float scalar, const vec2& vec);

std::istream& operator >>(std::istream& stream, vec2& vec);
std::ostream& operator <<(std::ostream& stream, const vec2& vec);


float length(const vec2& vec);
vec2 normalize(const vec2& vec);
float dot(const vec2& v1, const vec2& v2);