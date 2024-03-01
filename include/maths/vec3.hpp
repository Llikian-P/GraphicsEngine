/******************************************************************************************************
 * @file  vec3.cpp
 * @brief Declaration of the vec3 class
 ******************************************************************************************************/

#pragma once

#include <istream>
#include <ostream>

class vec3 {
public:
    vec3();
    vec3(float scalar);
    vec3(float x, float y, float z);
    vec3& operator =(const vec3&) = default;

    float& operator [](int index);

    void operator +=(const vec3& vec);
    void operator -=(const vec3& vec);
    void operator *=(const vec3& vec);
    void operator /=(const vec3& vec);

    void operator +=(float scalar);
    void operator -=(float scalar);
    void operator *=(float scalar);
    void operator /=(float scalar);

    union {
        struct { float x, y, z; };
        struct { float r, g, b; };
    };
};

using Point = vec3;
using Vector = vec3;
using RGB = vec3;

vec3 operator +(const vec3& v1, const vec3& v2);
vec3 operator -(const vec3& v1, const vec3& v2);
vec3 operator *(const vec3& v1, const vec3& v2);
vec3 operator /(const vec3& v1, const vec3& v2);

vec3 operator +(const vec3& vec, float scalar);
vec3 operator -(const vec3& vec, float scalar);
vec3 operator *(const vec3& vec, float scalar);
vec3 operator /(const vec3& vec, float scalar);

vec3 operator +(float scalar, const vec3& vec);
vec3 operator -(float scalar, const vec3& vec);
vec3 operator *(float scalar, const vec3& vec);
vec3 operator /(float scalar, const vec3& vec);

std::istream& operator >>(std::istream& stream, vec3& vec);
std::ostream& operator <<(std::ostream& stream, const vec3& vec);


float length(const vec3& vec);
vec3 normalize(const vec3& vec);
float dot(const vec3& v1, const vec3& v2);
vec3 cross(const vec3& v1, const vec3& v2);