//
// Created by BlackFlage on 20.12.2021.
//

#include "Mesh.h"

namespace vis
{

    Mesh::Mesh(std::vector <Vertex> a_vertices, std::vector<unsigned int> a_indices, unsigned int a_geometry_type)
    {
        m_vertices = std::move(a_vertices);
        m_indices = std::move(a_indices);
        m_geometry_type = a_geometry_type;
    }

    const std::vector<Vertex>& Mesh::get_vertices() const
    {
        return m_vertices;
    }

    const std::vector<unsigned int>& Mesh::get_indices() const
    {
        return m_indices;
    }

    unsigned int Mesh::get_geometry_type() const
    {
        return m_geometry_type;
    }
}