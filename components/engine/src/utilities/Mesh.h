//
// Created by BlackFlage on 15.11.2021.
//

#ifndef MAIN_MESH_H
#define MAIN_MESH_H

#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

using Vertex = float;
using Normal = glm::vec3;
using Index = unsigned int;
using TextureCoords = glm::vec2;

namespace vis
{
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> a_vertices,
             std::vector<Index> a_indices,
             std::vector<Normal> a_normals,
             std::vector<TextureCoords> a_textureCoords,
             std::vector<Index> a_vertexNormalIndices,
             std::vector<Index> a_textureCoordsIndices,
             GLint a_geometryType);

        const std::vector<Vertex>& get_vertices() const;
        const std::vector<Index>& get_indices() const;

        int get_vertices_count() const;
        int get_indices_count() const;

        GLint get_geometry_type() const;
    private:
        GLint m_geometryType;
        std::vector<Vertex> m_vertices;
        std::vector<Index> m_indices;
        std::vector<Normal> m_normals;
        std::vector<TextureCoords> m_textureCoords;
        std::vector<Index> m_vertexNormalIndices;
        std::vector<Index> m_textureCoordsIndices;
    };
}

#endif //MAIN_MESH_H
