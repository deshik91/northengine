//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_TEXTURE_H
#define NORTH_ENGINE_LANG_TEXTURE_H

#include <string>

class Texture {
public:
    explicit Texture(const char *path);

    Texture(unsigned char *data, int width, int height, int channels);

    virtual ~Texture();

    void Bind(unsigned int slot = 0) const;

    void Unbind() const;

    int GetWidth() const { return m_Width; }

    int GetHeight() const { return m_Height; }

    int GetChannels() const { return m_Channels; }

    int GetID() const { return m_TextureID; }


private:
    std::string m_FilePath;
protected:
    int m_TextureID;
    int m_Channels;
    int m_Width;
    int m_Height;
};

#endif //NORTH_ENGINE_LANG_TEXTURE_H
