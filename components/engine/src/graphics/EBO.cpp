//
// Created by BlackFlage on 20.10.2021.
//

#include "EBO.h"
#include <cstdint>

namespace vis
{

    EBO::EBO(std::vector<unsigned int> a_indices, unsigned int a_count)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_count * sizeof(unsigned int), &a_indices[0], GL_STATIC_DRAW);
    }

    EBO::~EBO()
    {
        glDeleteBuffers(1, &m_id);
    }
}