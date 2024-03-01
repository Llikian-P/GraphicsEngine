/******************************************************************************************************
 * @file  Camera.cpp
 * @brief Implementation of the Camera class
 ******************************************************************************************************/

#include "Camera.hpp"

#include <cmath>

#include "maths/constants.hpp"
#include "maths/functions.hpp"
#include "maths/transformations.hpp"

FirstPerson::FirstPerson(const Point& position, const Vector& front, const Vector& up)
    : position{position}, front{normalize(front)}, up{normalize(up)},
      movementSpeed{}, mouseSensitivity{0.1f}, yaw{-half_pi()}, pitch{} { }

Matrix4 FirstPerson::getLookAt() const {
    return lookAt(position, position + front, up);
}

Vector FirstPerson::right() const {
    return cross(front, up);
}

void FirstPerson::processKeyboardInputs(CameraControls control, float delta) {
    movementSpeed = delta * 5.0f;

    switch(control) {
        case CameraControls::forward:
            position += movementSpeed * front;
            break;
        case CameraControls::backward:
            position -= movementSpeed * front;
            break;
        case CameraControls::left:
            position -= movementSpeed * right();
            break;
        case CameraControls::right:
            position += movementSpeed * right();
            break;
        case CameraControls::upward:
            position += movementSpeed * up;
            break;
        case CameraControls::downward:
            position -= movementSpeed * up;
            break;
        default:
            break;
    }
}

void FirstPerson::processMouseInputs(float offsetX, float offsetY) {
    offsetX *= mouseSensitivity;
    offsetY *= mouseSensitivity;

    yaw += radians(offsetX);
    if(yaw > two_pi()) {
        yaw -= two_pi();
    } else if(yaw < -two_pi()) {
        yaw += two_pi();
    }

    pitch += radians(offsetY);
    if(pitch > half_pi() - 0.00001f) {
        pitch = half_pi() - 0.00001f;
    } else if(pitch < -half_pi() + 0.00001f) {
        pitch = -half_pi() + 0.00001f;
    }

    front.x = cosf(pitch) * cosf(yaw);
    front.y = sinf(pitch);
    front.z = cosf(pitch) * sinf(yaw);
}

ThirdPerson::ThirdPerson(const Point& position, const Point& target)
    : position{position}, target{target}, movementSpeed{}, mouseSensitivity{0.1f}, yaw{-half_pi()}, pitch{} { }

Matrix4 ThirdPerson::getLookAt() const {
    return lookAt(position, target, YAxis());
}

Vector ThirdPerson::direction() const {
    return normalize(position - target);
}

Vector ThirdPerson::right() const {
    return normalize(cross(YAxis(), direction()));
}

Vector ThirdPerson::up() const {
    return normalize(cross(direction(), right()));
}

void ThirdPerson::processKeyboardInputs(CameraControls control, float delta) {
    movementSpeed = delta * 5.0f;

    switch(control) {
        case CameraControls::forward:
            position -= movementSpeed * direction();
            break;
        case CameraControls::backward:
            position += movementSpeed * direction();
            break;
        default:
            break;
    }
}

void ThirdPerson::processMouseInputs(float offsetX, float offsetY) {
    offsetX *= mouseSensitivity;
    offsetY *= mouseSensitivity;

    yaw += radians(offsetX);
    if(yaw > two_pi()) {
        yaw -= two_pi();
    } else if(yaw < -two_pi()) {
        yaw += two_pi();
    }

    pitch += radians(offsetY);
    if(pitch > half_pi() - 0.00001f) {
        pitch = half_pi() - 0.00001f;
    } else if(pitch < -half_pi() + 0.00001f) {
        pitch = -half_pi() + 0.00001f;
    }

    float distance = length(position - target);

    position.x = target.x - distance * cosf(pitch) * cosf(yaw);
    position.y = target.y - distance * sinf(pitch);
    position.z = target.z - distance * cosf(pitch) * sinf(yaw);
}