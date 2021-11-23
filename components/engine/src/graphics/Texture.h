//
// Created by BlackFlage on 22.11.2021.
//

#ifndef MAIN_TEXTURE_H
#define MAIN_TEXTURE_H

#include <string>
#include "GL/glew.h"

namespace vis
{
    class Texture
    {
    public:
        Texture(const std::string& a_file_path);
        ~Texture();

        void bind() const;
        void unbind() const;
    private:
        void load_texture(const std::string& a_file_path, unsigned char** a_texture_data);
    private:
        GLuint m_id;

        int m_width;
        int m_height;
    };
}


#endif //MAIN_TEXTURE_H
