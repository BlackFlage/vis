//
// Created by BlackFlage on 13.11.2021.
//

#include "Model.h"

#include <utility>
#include <glm/gtc/matrix_transform.hpp>

namespace vis
{
    Model::Model(Mesh *a_mesh)
    :   m_mesh(a_mesh), m_position(glm::vec3(0.0f))
    {
        m_mesh->setup_mesh();
    }

    Model::Model(Mesh *a_mesh, glm::vec3 a_position)
            :   m_mesh(a_mesh), m_position(a_position)
    {
        m_mesh->setup_mesh();
    }

    Model::~Model()
    {
        delete m_mesh;
    }

    const Mesh *Model::get_mesh() const
    {
        return m_mesh;
    }

    const glm::mat4& Model::get_transform() const
    {
        glm::mat4 m_transform = glm::mat4(1.0f);
        m_transform = glm::translate(m_transform, m_position);

        return m_transform;
    }
}
