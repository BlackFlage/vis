//
// Created by BlackFlage on 22.11.2021.
//

#ifndef MAIN_TEXTURE_H
#define MAIN_TEXTURE_H

#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"

namespace vis
{
    class Texture
    {
    public:
        Texture(const std::string& a_file_path);
        Texture(const std::string& a_file_path, glm::vec2 a_uv0, glm::vec2 a_uv1);
        Texture(const Texture& rhs) = delete;
        Texture& operator=(const Texture& rhs) = delete;
        ~Texture();

        void bind() const;
        void unbind() const;

        std::uint16_t get_width() const;
        std::uint16_t get_height() const;
        const glm::ivec2& get_dimensions() const;
        const glm::vec2& get_uv0() const;
        const glm::vec2& get_uv1() const;

        const GLuint& get_id() const;
    private:
        GLuint m_id;

        glm::ivec2 m_dimensions;
        glm::vec2 m_uv0;
        glm::vec2 m_uv1;
    };
}


#endif //MAIN_TEXTURE_H
