/******************************************************************************************************
 * @file  ImageData.cpp
 * @brief Implementation of the ImageData class
 ******************************************************************************************************/

#include "ImageData.hpp"

#include <iostream>
#include <stb_image.h>
#include <stb_image_write.h>
#include <stdexcept>

ImageData::ImageData(const std::string& path) : width{}, height{}, colorChannels{}, data{}, isHeapAllocated{false} {
    stbi_set_flip_vertically_on_load(true);

    data = stbi_load(path.c_str(), &width, &height, &colorChannels, 0);
    if(!data) {
        throw std::runtime_error{"Image was not found at path: \"" + path + "\"."};
    }
    std::cout << "Read image: \"" + path.substr(path.find_last_of('/') + 1) + "\".\n";
}

ImageData::ImageData(const ImageData& im) : width{im.width}, height{im.height}, colorChannels{im.colorChannels}, isHeapAllocated{true} {
    const int size = width * height * colorChannels;

    data = new unsigned char[size];
    for(int i = 0 ; i < size ; ++i) {
        data[i] = im.data[i];
    }
}

ImageData& ImageData::operator =(const ImageData& im) {
    if(this == &im) { return *this; }

    if(isHeapAllocated) {
        delete data;
    } else {
        stbi_image_free(data);
    }

    width = im.width;
    height = im.height;
    colorChannels = im.colorChannels;

    const int size = width * height * colorChannels;

    data = new unsigned char[size];
    for(int i = 0 ; i < size ; ++i) {
        data[i] = im.data[i];
    }

    isHeapAllocated = true;

    return *this;
}

ImageData::~ImageData() {
    if(isHeapAllocated) {
        delete data;
    } else {
        stbi_image_free(data);
    }
}

// todo : check if this works
Color ImageData::operator ()(int i, int j) const {
    Color color;

    color.r = static_cast<float>(data[i + width * j]) / 255.f;
    color.g = static_cast<float>(data[i + width * j]) / 255.f;
    color.b = static_cast<float>(data[i + width * j]) / 255.f;
    color.a = (colorChannels == 4) ? static_cast<float>(data[i + width * j]) / 255.f : 1.0f;

    return color;
}

void ImageData::write(const std::string& path) const {
    bool success;

    if(path.find(".png") != std::string::npos) {
        success = stbi_write_png(path.c_str(), width, height, colorChannels, data, 0);
    } else if(path.find(".jpg") != std::string::npos) {
        success = stbi_write_jpg(path.c_str(), width, height, colorChannels, data, 100);
    } else if(path.find(".bmp") != std::string::npos) {
        success = stbi_write_bmp(path.c_str(), width, height, colorChannels, data);
    } else if(path.find(".tga") != std::string::npos) {
        success = stbi_write_tga(path.c_str(), width, height, colorChannels, data);
    } else {
        throw std::runtime_error{"File extension not supported: \"" + path + "\"."};
    }

    if(!success) {
        throw std::runtime_error{"Failed to write image: \"" + path + "\".\n"};
    }
    std::cout << "LOG : Wrote image: \"" << path << "\".\n";
}

int ImageData::getWidth() const {
    return width;
}

int ImageData::getHeight() const {
    return height;
}

int ImageData::getColorChannels() const {
    return colorChannels;
}

const unsigned char* ImageData::getData() const {
    return data;
}