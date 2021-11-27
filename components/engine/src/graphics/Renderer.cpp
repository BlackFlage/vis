//
// Created by BlackFlage on 19.10.2021.
//

#include "Renderer.h"
#include "Application.h"
#include "Macro.h"

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
        glActiveTexture(GL_TEXTURE0);
        float radius = 40.0f;
        float light_x = std::sin(Application::get_instance()->get_time_passed()) * radius;
        float light_z = std::cos(Application::get_instance()->get_time_passed()) * radius;
        a_shader->set_uniform_3f("u_light_color", 1.0f, 1.0f, 1.0f);
        a_shader->set_uniform_3f("u_light_position", light_x, 1.0f, light_z);
        a_shader->set_uniform_mat4("u_projection", a_camera->get_projection());
        a_shader->set_uniform_mat4("u_view", a_camera->get_view());
        a_shader->set_uniform_mat4("u_model", a_model->get_transform());
        a_shader->set_uniform_3f("u_color", 1.0f, 1.0f, 1.0f);
        a_shader->bind();

        CheckGLError();

        a_model->bind_texture();
        for(const auto& m : a_model->get_meshes())
        {
            m->bind();
            glDrawArrays(GL_QUADS, 0, m->get_vertices_count());
        }
    }
}

