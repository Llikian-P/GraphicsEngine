/******************************************************************************************************
 * @file  Light.hpp
 * @brief Declaration of the Light class
 ******************************************************************************************************/

#pragma once

#include "maths/constants.hpp"
#include "maths/vec3.hpp"
#include "maths/vec4.hpp"

class Light {
public:
    Light(const Point& position, const Color& ambient, const Color& diffuse, const Color& specular);

    Point position;

    Color ambient;
    Color diffuse;
    Color specular;
};