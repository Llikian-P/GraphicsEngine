/******************************************************************************************************
 * @file  vec4.cpp
 * @brief Declaration of the vec4 class
 ******************************************************************************************************/

#pragma once

#include <istream>
#include <ostream>

class vec4 {
public:
    vec4();
    vec4(float scalar);
    vec4(float x, float y, float z, float w);
    vec4(float scalar, float alpha);
    vec4& operator =(const vec4&) = default;

    float& operator [](int index);

    void operator +=(const vec4& vec);
    void operator -=(const vec4& vec);
    void operator *=(const vec4& vec);
    void operator /=(const vec4& vec);

    void operator +=(float scalar);
    void operator -=(float scalar);
    void operator *=(float scalar);
    void operator /=(float scalar);

    union {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
    };
};

using Color = vec4;

vec4 operator +(const vec4& v1, const vec4& v2);
vec4 operator -(const vec4& v1, const vec4& v2);
vec4 operator *(const vec4& v1, const vec4& v2);
vec4 operator /(const vec4& v1, const vec4& v2);

vec4 operator +(const vec4& vec, float scalar);
vec4 operator -(const vec4& vec, float scalar);
vec4 operator *(const vec4& vec, float scalar);
vec4 operator /(const vec4& vec, float scalar);

vec4 operator +(float scalar, const vec4& vec);
vec4 operator -(float scalar, const vec4& vec);
vec4 operator *(float scalar, const vec4& vec);
vec4 operator /(float scalar, const vec4& vec);

std::istream& operator >>(std::istream& stream, vec4& vec);
std::ostream& operator <<(std::ostream& stream, const vec4& vec);


float length(const vec4& vec);
vec4 normalize(const vec4& vec);
float dot(const vec4& v1, const vec4& v2);