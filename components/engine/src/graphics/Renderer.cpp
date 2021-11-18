//
// Created by BlackFlage on 19.10.2021.
//

#include "Renderer.h"

namespace vis
{
    void Renderer::change_background_color(float r, float g, float b, float alpha)
    {
        glClearColor(r, g, b, alpha);
    }

    void Renderer::render(float r, float g, float b, float size, Shader *a_shader)
    {

    }

    void Renderer::render(Model *a_model, Camera* a_camera, Shader *a_shader)
    {
        const Mesh* mesh = a_model->get_mesh();

        mesh->bind();

        a_shader->set_uniform_3f("u_light_color", 1.0f, 0.0f, 0.3f);
        a_shader->set_uniform_3f("u_light_position", -10.0f, 5.0f, 4.0f);
        a_shader->set_uniform_mat4("u_view", a_camera->get_transform());
        a_shader->set_uniform_mat4("u_model", a_model->get_transform());
        a_shader->set_uniform_3f("u_color", 1.0f, 1.0f, 1.0f);
        a_shader->bind();

        CheckGLError();
        glDrawArrays(mesh->get_geometry_type(), 0, mesh->get_vertices_count());
    }
}

