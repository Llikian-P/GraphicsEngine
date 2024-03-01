/******************************************************************************************************
 * @file  functions.cpp
 * @brief
 ******************************************************************************************************/

#include "maths/functions.hpp"

#include "maths/constants.hpp"

float radians(float angle) {
    return angle * pi() / 180.0f;
}

float degrees(float angle) {
    return angle * 180.0f / pi();
}

Point bezierCurve(const Point& P0, const Point& P1, const Point& P2, const Point& P3, float t) {
    const float T = 1 - t;

    return P0 * T * T * T +
           P1 * T * T * t * 3 +
           P2 * T * t * t * 3 +
           P3 * t * t * t;
}