/******************************************************************************************************
 * @file  Camera.hpp
 * @brief Declaration of the Camera class
 ******************************************************************************************************/

#pragma once

#include "maths/vec3.hpp"
#include "maths/Matrix4.hpp"

enum class CameraControls {
    forward,
    backward,
    left,
    right,
    upward,
    downward
};

class FirstPerson {
public:
    FirstPerson(const Point& position,
                const Vector& front = Point{0.0f, 0.0f, -1.0f},
                const Vector& up = Vector{0.0f, 1.0f, 0.0f});

    [[nodiscard]] Matrix4 getLookAt() const;
    [[nodiscard]] Vector right() const;

    void processKeyboardInputs(CameraControls control, float delta);
    void processMouseInputs(float offsetX, float offsetY);

    Point position;
    Vector front;
    Vector up;

    float movementSpeed;
    float mouseSensitivity;
    float yaw;
    float pitch;
};

class ThirdPerson {
public:
    ThirdPerson(const Point& position, const Point& target = Point{});

    [[nodiscard]] Matrix4 getLookAt() const;
    [[nodiscard]] Vector direction() const;
    [[nodiscard]] Vector right() const;
    [[nodiscard]] Vector up() const;

    void processKeyboardInputs(CameraControls control, float delta);
    void processMouseInputs(float offsetX, float offsetY);

    Point position;
    Point target;

    float movementSpeed;
    float mouseSensitivity;
    float yaw;
    float pitch;
};
