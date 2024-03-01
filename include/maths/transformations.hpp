/******************************************************************************************************
 * @file  functions.hpp
 * @brief
 ******************************************************************************************************/

#pragma once

#include "Matrix4.hpp"
#include "vec3.hpp"

Matrix4 rotate(float angle, const Vector& axis);
Matrix4 rotate(const Vector& v1, const Vector& v2);
Matrix4 rotateX(float angle);
Matrix4 rotateY(float angle);
Matrix4 rotateZ(float angle);
Matrix4 translate(const Vector& vector);
Matrix4 translate(float x, float y, float z);
Matrix4 scale(float x, float y, float z);
Matrix4 scale(float scalar);

Matrix4 lookAt(const Point& eye, const Point& center, const Vector& up);
Matrix4 perspective(float fov, float aspect, float near, float far);