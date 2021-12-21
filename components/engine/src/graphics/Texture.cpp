//
// Created by BlackFlage on 22.11.2021.
//

#include "Texture.h"
#include "BMPLoader.h"
#include "Macro.h"

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

        uint8_t* texture_data = nullptr;
        load_texture(a_file_path, &texture_data);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        CheckGLError();

        delete[] texture_data;
    }

    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::load_texture(const std::string& a_file_path, unsigned char** a_texture_data)
    {
        *a_texture_data = BMPLoader::load_from_file(a_file_path, &m_width, &m_height, true);
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