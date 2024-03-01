/******************************************************************************************************
 * @file  ImageData.hpp
 * @brief Declaration of the ImageData class
 ******************************************************************************************************/

#pragma once

#include <string>

#include "maths/vec4.hpp"

class ImageData {
public:
    ImageData(const std::string& path);
    ImageData(const ImageData& im);
    ImageData& operator =(const ImageData& im);

    ~ImageData();

    [[nodiscard]] Color operator ()(int i, int j) const;

    void write(const std::string& path) const;

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getColorChannels() const;
    [[nodiscard]] const unsigned char* getData() const;

private:
    int width;
    int height;
    int colorChannels;

    unsigned char* data;

    bool isHeapAllocated;
};