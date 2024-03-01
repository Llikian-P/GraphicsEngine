/******************************************************************************************************
 * @file  Light.cpp
 * @brief Implementation of the Light class
 ******************************************************************************************************/

#include "Light.hpp"

Light::Light(const Point& position, const Color& ambient, const Color& diffuse, const Color& specular)
    : position{position}, ambient{ambient}, diffuse{diffuse}, specular{specular} { }