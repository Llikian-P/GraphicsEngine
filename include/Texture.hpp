/******************************************************************************************************
 * @file  Texture.hpp
 * @brief Declaration of the Texture class
 ******************************************************************************************************/

#pragma once

#include <glad/glad.h>

#include "ImageData.hpp"

class Texture {
public:
    Texture();
    Texture(const ImageData& image);

    ~Texture();

    void bind() const;

    [[nodiscard]] unsigned getId() const;

private:
    unsigned id;
};