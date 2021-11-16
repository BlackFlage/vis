//
// Created by BlackFlage on 15.11.2021.
//

#include "Mesh.h"

vis::Mesh::Mesh(std::vector<Vertex> a_vertices,
                std::vector<Index> a_indices,
                std::vector<Normal> a_normals,
                std::vector<TextureCoords> a_textureCoords,
                std::vector<Index> a_vertexNormalIndices,
                std::vector<Index> a_textureCoordsIndices,
                GLint a_geometryType)
{
    m_vertices = std::move(a_vertices);
    m_indices = std::move(a_indices);
    m_normals = std::move(a_normals);
    m_textureCoords = std::move(a_textureCoords);
    m_vertexNormalIndices = std::move(a_vertexNormalIndices);
    m_textureCoordsIndices = std::move(a_textureCoordsIndices);
    m_geometryType = a_geometryType;
}

const std::vector<Vertex> &vis::Mesh::get_vertices() const
{
    return m_vertices;
}

const std::vector<Index> &vis::Mesh::get_indices() const
{
    return m_indices;
}

int vis::Mesh::get_vertices_count() const
{
    return m_vertices.size();
}

int vis::Mesh::get_indices_count() const
{
    return m_indices.size();
}

GLint vis::Mesh::get_geometry_type() const
{
    return m_geometryType;
}
