//
// Created by BlackFlage on 13.11.2021.
//

#include "Model.h"

#include <utility>

namespace vis
{
    Model::Model(Mesh *a_mesh)
    :   m_mesh(a_mesh)
    {

    }

    Model::~Model()
    {
        delete m_mesh;
    }

    const Mesh *Model::get_mesh() const
    {
        return m_mesh;
    }
}
