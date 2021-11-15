//
// Created by BlackFlage on 19.10.2021.
//

#include "Renderer.h"
#include "GL/glew.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

namespace vis
{
    void Renderer::change_background_color(float r, float g, float b, float alpha)
    {
        glClearColor(r, g, b, alpha);
    }

    void Renderer::render(float r, float g, float b, float size, Shader *a_shader)
    {
        float vertices[] = {
                -size, -size, 1.0f,
                size, -size, 1.0f,
                size, size, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 2
        };

        VAO vao;
        vao.bind();
        VBO vbo(vertices, 9);
        EBO ebo(indices, 3);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        a_shader->set_uniform_3f("u_color", r / 2 + 0.1f, b / 3 + 0.25f, g / 2);
        a_shader->bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::render(Model *a_model, Shader *a_shader)
    {
        const Mesh* mesh = a_model->get_mesh();

        VAO vao;
        vao.bind();
        auto vert = mesh->get_vertices();
        auto ind = mesh->get_indices();
        VBO vbo(&vert[0], mesh->get_vertices_count());
        EBO ebo(&ind[0], mesh->get_indices_count());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        a_shader->set_uniform_3f("u_color", 1.0f, 0.0f, 1.0f);
        a_shader->bind();

        glDrawElements(mesh->get_geometry_type(), mesh->get_indices_count(), GL_UNSIGNED_INT, nullptr);
    }
}

