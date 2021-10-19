//
// Created by BlackFlage on 10.10.2021.
//

#include "VBO.h"

vis::VBO::VBO(float* a_vertices)
{
    glGenBuffers(1, &m_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(a_vertices), a_vertices, GL_STATIC_DRAW);
}
