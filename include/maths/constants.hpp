/******************************************************************************************************
 * @file  constants.hpp
 * @brief
 ******************************************************************************************************/

#pragma once

#include "Matrix4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

constexpr inline float pi() { return 3.141593f; }

constexpr inline float two_pi() { return 6.283185f; }

constexpr inline float half_pi() { return 1.570796f; }

constexpr inline float quarter_pi() { return 0.7853982f; }

constexpr inline float root_two_over_two() { return 0.7071068f; }

inline Vector XAxis() { return Vector(1.0f, 0.0f, 0.0f); }

inline Vector YAxis() { return Vector(0.0f, 1.0f, 0.0f); }

inline Vector ZAxis() { return Vector(0.0f, 0.0f, 1.0f); }

inline Color White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }

inline Color Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }

inline Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }

inline Color Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }

inline Color Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }

inline Color Cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }

inline Color Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }

inline Color Yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }

inline Matrix4 Identity() { return Matrix4(); }