//
// Created by BlackFlage on 22.11.2021.
//

#include "Texture.h"
#include "Macro.h"
#include "stb_image.h"
#include "Logger.h"

namespace vis
{

    Texture::Texture(const std::string &a_file_path)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int channels;
        unsigned char* texture_data = nullptr;
        texture_data = stbi_load(a_file_path.c_str(), &m_width, &m_height, &channels, STBI_rgb_alpha);

        if(!texture_data)
        {
            LOG_ERROR("Failed to load texture: {0}", a_file_path.c_str());
            glDeleteTextures(1, &m_id);
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        CheckGLError();

        stbi_image_free(texture_data);
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_id);
    }

    GLuint Texture::get_id() const
    {
        return m_id;
    }

    int Texture::get_width() const
    {
        return m_width;
    }

    int Texture::get_height() const
    {
        return m_height;
    }
}