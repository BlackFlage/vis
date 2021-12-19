//
// Created by BlackFlage on 19.10.2021.
//

#include "Renderer.h"
#include "Macro.h"

namespace vis
{
    unsigned int Renderer::vertex_array;
    unsigned int Renderer::vertex_buffer;
    unsigned int Renderer::index_buffer;
    unsigned int Renderer::indices_count;
    Shader* Renderer::m_shader;
    Camera* Renderer::m_camera;

    void Renderer::change_background_color(float r, float g, float b, float alpha)
    {
        glClearColor(r, g, b, alpha);
    }

    void Renderer::begin()
    {

    }

    void Renderer::end()
    {

    }

    void Renderer::render(MeshRender& a_mesh)
    {
        glGenVertexArrays(1, &vertex_array);
        glGenBuffers(1, &vertex_buffer);
        glGenBuffers(1, &index_buffer);

        glBindVertexArray(vertex_array);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, a_mesh.m_vertices.size() * sizeof(Vertex), &(a_mesh.m_vertices[0]), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_mesh.m_indices.size() * sizeof(unsigned int), &(a_mesh.m_indices[0]), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 2));

        m_shader->set_uniform_3f("u_light_color", 1.0f, 1.0f, 1.0f);
        m_shader->set_uniform_3f("u_light_position", 0.0f, 10.0f, -10.0f);
        m_shader->set_uniform_mat4("u_projection", m_camera->get_projection());
        m_shader->set_uniform_mat4("u_view", m_camera->get_view());
        m_shader->set_uniform_mat4("u_model", a_mesh.m_model);
        m_shader->set_uniform_3f("u_color", a_mesh.m_color.x, a_mesh.m_color.y, a_mesh.m_color.z);

        m_shader->bind();
        glDrawArrays(GL_TRIANGLES, 0, a_mesh.m_vertices.size());

        clean_buffers();
    }

    void Renderer::clean_buffers()
    {
        glDeleteVertexArrays(1, &vertex_array);
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteBuffers(1, &index_buffer);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Renderer::submit_data(const MeshRender &a_mesh)
    {

    }

    void Renderer::set_camera(Camera *a_camera)
    {
        m_camera = a_camera;
    }

    void Renderer::set_shader(Shader *a_shader)
    {
        m_shader = a_shader;
    }
}

