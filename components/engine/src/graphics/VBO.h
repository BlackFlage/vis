//
// Created by BlackFlage on 10.10.2021.
//

#ifndef MAIN_VBO_H
#define MAIN_VBO_H

#include "GL/glew.h"
#include <vector>
#include "Vertex.h"

namespace vis
{
    class VBO
    {
    public:
        VBO(const std::vector<Vertex>& a_vertices, unsigned int a_count);
        ~VBO();

        inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

        inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
    private:
        GLuint m_id;
    };
}



#endif //MAIN_VBO_H
