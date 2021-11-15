//
// Created by BlackFlage on 19.10.2021.
//

#ifndef MAIN_VAO_H
#define MAIN_VAO_H

#include "GL/glew.h"

namespace vis
{
    class VAO
    {
    public:
        VAO();
        ~VAO();

        inline void bind() const { glBindVertexArray(m_id); }
        inline void unbind() const { glBindVertexArray(0); }
    private:
        GLuint m_id;
    };
}


#endif //MAIN_VAO_H
