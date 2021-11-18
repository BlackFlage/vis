//
// Created by BlackFlage on 15.11.2021.
//

#include "Mesh.h"

namespace vis
{
    Mesh::Mesh(std::vector<Vertex> a_vertices, std::vector<unsigned int> a_indices, GLint a_geometryType)
    :   m_vertices(std::move(a_vertices)), m_indices(std::move(a_indices)), m_geometryType(a_geometryType)
    {

    }

    Mesh::~Mesh()
    {

    }

    bool Mesh::setup_mesh()
    {
        glGenVertexArrays(1, &m_vertexArray);
        glGenBuffers(1, &m_vertexBuffer);
        glGenBuffers(1, &m_indexBuffer);

        glBindVertexArray(m_vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (sizeof(float) * 3));

        glBindVertexArray(0);

        return true;
    }

    void Mesh::bind() const
    {
        glBindVertexArray(m_vertexArray);
    }

    GLint Mesh::get_geometry_type() const
    {
        return m_geometryType;
    }

    GLint Mesh::get_vertices_count() const
    {
        return m_vertices.size();
    }

    GLint Mesh::get_indices_count() const
    {
        return m_indices.size();
    }
}
