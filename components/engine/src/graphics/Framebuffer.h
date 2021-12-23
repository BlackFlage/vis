//
// Created by BlackFlage on 23.12.2021.
//

#ifndef MAIN_FRAMEBUFFER_H
#define MAIN_FRAMEBUFFER_H

#include "GL/glew.h"

namespace vis
{
    class Framebuffer
    {
    public:
        Framebuffer(int a_width, int a_height);

        void bind() const;
        void unbind() const;

        GLuint get_texture_id() const;
    private:
        GLuint m_id;
        GLuint m_texture_id;
        GLuint m_render_buffer_id;
    };
}

#endif //MAIN_FRAMEBUFFER_H
