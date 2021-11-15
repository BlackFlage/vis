//
// Created by BlackFlage on 10.10.2021.
//

#include "VBO.h"

vis::VBO::VBO(float a_vertices[], unsigned int a_count)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, a_count * sizeof(float), &a_vertices[0], GL_STATIC_DRAW);
}

vis::VBO::~VBO()
{
    glDeleteBuffers(1, &m_id);
}
