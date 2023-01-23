//
// Created by deshik on 23.01.2023.
//

#include "northengine/graphics/texture.h"

#include <glad/glad.h>


#include <string>
#include <iostream>

int GenerateTexture(unsigned char *data, int width, int height, int channels) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int format = 0;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

#include <SDL2/SDL_image.h>

Texture::Texture(const char *path) {
    m_FilePath = path;
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        std::cout << "Failed to load texture: " << path << std::endl;
        return;
    }

    m_Width = surface->w;
    m_Height = surface->h;
    m_Channels = surface->format->BytesPerPixel;

    m_TextureID = GenerateTexture((unsigned char *) surface->pixels, m_Width, m_Height, m_Channels);

    SDL_FreeSurface(surface);
}

Texture::Texture(unsigned char *data, int width, int height, int channels) {
    m_Width = width;
    m_Height = height;
    m_Channels = channels;

    m_TextureID = GenerateTexture(data, m_Width, m_Height, m_Channels);
}

Texture::~Texture() {
    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&m_TextureID));
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
