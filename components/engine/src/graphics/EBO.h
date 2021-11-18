//
// Created by BlackFlage on 20.10.2021.
//

#ifndef MAIN_EBO_H
#define MAIN_EBO_H

#include "GL/glew.h"
#include <vector>

namespace vis
{
    class EBO
    {
    public:
        EBO(std::vector<unsigned int> a_indices, unsigned int a_count);
        ~EBO();

        inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
        inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);}
    private:
        GLuint m_id;
    };
}


#endif //MAIN_EBO_H
