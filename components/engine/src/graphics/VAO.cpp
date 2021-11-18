//
// Created by BlackFlage on 19.10.2021.
//

#include "VAO.h"
#include "glm/glm.hpp"

namespace vis
{
    VAO::VAO()
    {
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void VAO::add_layout()
    {
    }
}

