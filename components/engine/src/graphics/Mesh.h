//
// Created by BlackFlage on 15.11.2021.
//

#ifndef MAIN_MESH_H
#define MAIN_MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"

namespace vis
{
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> a_vertices, std::vector<unsigned int> a_indices, GLint a_geometryType);
        ~Mesh();

        void bind() const;

        GLint get_geometry_type() const;
        GLint get_vertices_count() const;
        GLint get_indices_count() const;
    private:
        bool setup_mesh();
    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        unsigned int  m_vertexArray;
        unsigned int  m_vertexBuffer;
        unsigned int  m_indexBuffer;

        GLint m_geometryType;
    };
}

#endif //MAIN_MESH_H
