//
// Created by BlackFlage on 22.11.2021.
//

#include "Texture.h"
#include "Macro.h"
#include "../../../vendor/stbimage/stb_image.h"
#include "Logger.h"

namespace vis
{

    Texture::Texture(const std::string &a_file_path)
    : Texture(a_file_path, {0.0f, 0.0f}, {1.0f, 1.0f}){}

    Texture::Texture(const std::string &a_file_path, glm::vec2 a_uv0, glm::vec2 a_uv1)
    : m_uv0(a_uv0), m_uv1(a_uv1)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int channels;
        unsigned char* texture_data = nullptr;
        texture_data = stbi_load(a_file_path.c_str(), &m_dimensions.x, &m_dimensions.y, &channels, STBI_rgb_alpha);

        if(!texture_data)
        {
            LOG_ERROR("Failed to load texture: {0}", a_file_path.c_str());
            glDeleteTextures(1, &m_id);
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_dimensions.x, m_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
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

    const GLuint& Texture::get_id() const
    {
        return m_id;
    }

    std::uint16_t Texture::get_width() const
    {
        return m_dimensions.x;
    }

    std::uint16_t Texture::get_height() const
    {
        return m_dimensions.y;
    }

    const glm::ivec2& Texture::get_dimensions() const
    {
        return m_dimensions;
    }

    const glm::vec2& Texture::get_uv0() const
    {
        return m_uv0;
    }

    const glm::vec2& Texture::get_uv1() const
    {
        return m_uv1;
    }
}