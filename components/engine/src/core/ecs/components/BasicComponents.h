//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_BASICCOMPONENTS_H
#define MAIN_BASICCOMPONENTS_H

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace vis
{
    struct Transform
    {
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
    };

    struct Color
    {
        glm::vec3 m_color;
    };

    struct RigidBody
    {
        float vel_x;
        float vel_y;
        float vel_z;
    };

    struct Vertex
    {
        glm::vec3 m_position;
        glm::vec3 m_normals;
        glm::vec2 m_textureCoords;
    };

    struct VertexRender
    {
        glm::vec3 m_position;
        glm::vec3 m_normals;
        glm::vec2 m_textureCoords;
        glm::vec3 m_color;
        glm::mat4 m_transform;
    };

    struct Mesh
    {
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::string m_name;
        unsigned int m_geometry_type;
    };

    struct MeshRender
    {
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        glm::mat4 m_model;
        glm::vec3 m_color;
        unsigned int m_geometry_type;
    };
}

#endif //MAIN_BASICCOMPONENTS_H
