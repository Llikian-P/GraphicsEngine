/******************************************************************************************************
 * @file  Texture.cpp
 * @brief Implementation of the Texture class
 ******************************************************************************************************/

#include "Texture.hpp"

Texture::Texture() : id{} {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const ImageData& image) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int format;
    if(image.getColorChannels() == 4) {
        format = GL_RGBA;
    } else {
        format = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.getWidth(), image.getHeight(),
                 0, format, GL_UNSIGNED_BYTE, image.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

unsigned Texture::getId() const {
    return id;
}
