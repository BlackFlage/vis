//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_MESH_H
#define MAIN_MESH_H

#include <vector>

#include "glm/glm.hpp"

namespace vis
{
    struct Vertex
    {
        glm::vec3 m_position;
        glm::vec3 m_normals;
        glm::vec2 m_textureCoords;
    };

    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> a_vertices, std::vector<unsigned int> a_indices, unsigned int a_geometry_type);

        const std::vector<Vertex>& get_vertices() const;
        const std::vector<unsigned int>& get_indices() const;
        unsigned int get_geometry_type() const;
    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        unsigned int m_geometry_type;
    };
}

#endif //MAIN_MESH_H
