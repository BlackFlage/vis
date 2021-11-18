//
// Created by BlackFlage on 10.10.2021.
//

#include "VBO.h"

vis::VBO::VBO(const std::vector<Vertex>& a_vertices, unsigned int a_count)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, a_vertices.size() * sizeof(Vertex), &a_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

vis::VBO::~VBO()
{
    glDeleteBuffers(1, &m_id);
}
