//
// Created by BlackFlage on 02.01.2022.
//

#include "Grid.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace vis
{

    const std::vector<unsigned int> &Grid::get_indices() const
    {
        return m_indices;
    }

    const std::vector<Vertex> &Grid::get_vertices() const
    {
        return m_vertices;
    }

    Shader *Grid::get_shader() const
    {
        return m_shader;
    }

    bool Grid::create(std::uint16_t width, std::uint16_t height)
    {
        int index = 0;
        for(int i = 0; i <= width; i++)
        {
            m_vertices.push_back(Vertex{.m_position = glm::vec3(i, 0, 0), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});
            m_vertices.push_back(Vertex{.m_position = glm::vec3(i, 0, height), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});
            m_indices.push_back(index++);
            m_indices.push_back(index++);
        }

        for(int i = 0; i <= height; i++)
        {
            m_vertices.push_back(Vertex{.m_position = glm::vec3(0, 0, i), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});
            m_vertices.push_back(Vertex{.m_position = glm::vec3(width, 0, i), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});
            m_indices.push_back(index++);
            m_indices.push_back(index++);
        }

        /*m_vertices.push_back(Vertex{.m_position = glm::vec3(-1.0f, 1.0f, 0.0f), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});
        m_vertices.push_back(Vertex{.m_position = glm::vec3(-1.0f, -1.0f, 0.0f), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});
        m_vertices.push_back(Vertex{.m_position = glm::vec3(1.0f, -1.0f, 0.0f), .m_normals = glm::vec3(0.0f), .m_textureCoords = glm::vec2(0.0f)});*/

        m_shader = Shader::create_shader("../engine_assets/shaders/vertex_grid.glsl", "../engine_assets/shaders/fragment_grid.glsl");
        m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
        m_width = width;
        m_height = height;

        return m_shader != nullptr;
    }

    glm::mat4 Grid::get_model_mat() const
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_pos);

        return model;
    }

    std::uint16_t Grid::get_width() const
    {
        return m_width;
    }

    std::uint16_t Grid::get_height() const
    {
        return m_height;
    }
}