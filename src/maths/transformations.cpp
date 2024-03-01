/******************************************************************************************************
 * @file  transformations.cpp
 * @brief
 ******************************************************************************************************/

#include "maths/transformations.hpp"

#include <cmath>

#include "maths/functions.hpp"

Matrix4 rotate(float angle, const Vector& axis) {
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vector nAxis = normalize(axis);
    Vector temp = (1.0f - cosine) * nAxis;

    return Matrix4{cosine + temp[0] * nAxis[0], temp[0] * nAxis[1] + sine * nAxis[2], temp[0] * nAxis[2] - sine * nAxis[1],
                   temp[1] * nAxis[0] - sine * nAxis[2], cosine + temp[1] * nAxis[1], temp[1] * nAxis[2] + sine * nAxis[0],
                   temp[2] * nAxis[0] + sine * nAxis[1], temp[2] * nAxis[1] - sine * nAxis[0], cosine + temp[2] * nAxis[2]};
}

Matrix4 rotate(const Vector& v1, const Vector& v2) {
    float angle = acosf(dot(v1, v2) / (length(v1) * length(v2)));

    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vector axis = normalize(cross(v1, v2));
    Vector temp = (1.0f - cosine) * axis;

    return Matrix4{cosine + temp[0] * axis[0], temp[1] * axis[0] - sine * axis[2], temp[2] * axis[0] + sine * axis[1],
                   temp[0] * axis[1] + sine * axis[2], cosine + temp[1] * axis[1], temp[2] * axis[1] - sine * axis[0],
                   temp[0] * axis[2] - sine * axis[1], temp[1] * axis[2] + sine * axis[0], cosine + temp[2] * axis[2]};

//    return transpose(rotate(acosf(dot(v1, v2) / (length(v1) * length(v2))), cross(v1, v2)));
}

Matrix4 rotateX(float angle) {
    float rad = radians(angle);
    float cosine = cosf(rad);
    float sine = sinf(rad);

    return Matrix4{1.0f, 0.0f, 0.0f,
                   0.0f, cosine, -sine,
                   0.0f, sine, cosine};
}

Matrix4 rotateY(float angle) {
    float rad = radians(angle);
    float cosine = cosf(rad);
    float sine = sinf(rad);

    return Matrix4{cosine, 0.0f, sine,
                   0.0f, 1.0f, 0.0f,
                   -sine, 0.0f, cosine};
}

Matrix4 rotateZ(float angle) {
    float rad = radians(angle);
    float cosine = cosf(rad);
    float sine = sinf(rad);

    return Matrix4{cosine, -sine, 0.0f,
                   sine, cosine, 0.0f,
                   0.0f, 0.0f, 1.0f};
}

Matrix4 translate(const Vector& vector) {
    return Matrix4{1.0f, 0.0f, 0.0f, vector.x,
                   0.0f, 1.0f, 0.0f, vector.y,
                   0.0f, 0.0f, 1.0f, vector.z,
                   0.0f, 0.0f, 0.0f, 1.0f};
}

Matrix4 translate(float x, float y, float z) {
    return Matrix4{1.0f, 0.0f, 0.0f, x,
                   0.0f, 1.0f, 0.0f, y,
                   0.0f, 0.0f, 1.0f, z,
                   0.0f, 0.0f, 0.0f, 1.0f};
}

Matrix4 scale(float x, float y, float z) {
    return Matrix4{x, 0.0f, 0.0f,
                   0.0f, y, 0.0f,
                   0.0f, 0.0f, z};
}

Matrix4 scale(float scalar) {
    return Matrix4{scalar, 0.0f, 0.0f,
                   0.0f, scalar, 0.0f,
                   0.0f, 0.0f, scalar};
}

Matrix4 lookAt(const Point& eye, const Point& center, const Vector& up) {
    vec3 front = normalize(center - eye);
    vec3 side = normalize(cross(front, up));
    vec3 Up = normalize(cross(side, front));

    return Matrix4{side.x, side.y, side.z, -dot(side, eye),
                   Up.x, Up.y, Up.z, -dot(Up, eye),
                   -front.x, -front.y, -front.z, dot(front, eye),
                   0.0f, 0.0f, 0.0f, 1.0f};
}

Matrix4 perspective(float fov, float aspect, float near, float far) {
    return Matrix4{1.0f / (aspect * tanf(0.5f * fov)), 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f / tanf(0.5f * fov), 0.0f, 0.0f,
                   0.0f, 0.0f, -(far + near) / (far - near), -(2.0f * far * near) / (far - near),
                   0.0f, 0.0f, -1.0f, 0.0f};
}