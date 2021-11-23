//
// Created by BlackFlage on 16.11.2021.
//

#ifndef MAIN_VERTEX_H
#define MAIN_VERTEX_H

#include "glm/glm.hpp"

namespace vis
{
    struct Vertex
    {
        Vertex(glm::vec3 a_position, glm::vec3 a_normal, glm::vec2 a_textureCoords)
        :   m_position(a_position), m_normal(a_normal), m_textureCoords(a_textureCoords) {}

        glm::vec3 m_position;
        glm::vec3 m_normal;
        glm::vec2 m_textureCoords;
    };
}


#endif //MAIN_VERTEX_H
