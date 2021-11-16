//
// Created by BlackFlage on 13.11.2021.
//

#include "Model.h"

#include <utility>
#include <glm/gtc/matrix_transform.hpp>

namespace vis
{
    Model::Model(Mesh *a_mesh)
    :   m_mesh(a_mesh)
    {
        m_transform = glm::mat4(1.0f);
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
        return m_transform;
    }
}
