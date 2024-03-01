/******************************************************************************************************
 * @file  functions.hpp
 * @brief
 ******************************************************************************************************/

#pragma once

#include "maths/vec3.hpp"

float radians(float angle);
float degrees(float angle);

Point bezierCurve(const Point& P0, const Point& P1, const Point& P2, const Point& P3, float t);