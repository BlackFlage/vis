//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_SANDBOX_H
#define VISUAL_SANDBOX_H

#include "Layer.h"
#include <iostream>
#include <cmath>
#include "Gl/gl.h"
#include "Renderer.h"
#include "OBJLoader.h"
#include "Camera.h"
#include "event/KeyboardEvent.h"
#include <functional>
#include "Application.h"
#include "Texture.h"

namespace vis
{
    class Sandbox : public Layer
    {
    public:
        Sandbox()
        {
            m_shader = nullptr;
            m_camera = nullptr;
        }

        ~Sandbox() override
        {

        }

        void on_event(Event& a_event) override
        {
            EventDispatcher dispatcher(a_event);
            dispatcher.dispatch<KeyPressEvent>([this](auto&& event) { move_camera(std::forward<decltype(event)>(event)); });
            dispatcher.dispatch<WindowResizeEvent>([this](auto&& event) { on_window_resize_event(std::forward<decltype(event)>(event)); });
            dispatcher.dispatch<MouseMoveEvent>([this](auto&& event) { on_mouse_move_event(std::forward<decltype(event)>(event)); });
        }

        void on_update() override
        {

        }

        void on_render() override
        {
            Renderer::change_background_color(0.0f, 0.0f, 0.0f, 1.0f);

            for(const auto& m : m_models)
            {
                Renderer::render(m, m_camera, m_shader);
            }
        }

        void on_attach() override
        {
            m_shader = Shader::create_shader_name("vertex.glsl", "fragment.glsl");
            m_models.push_back(new Model({"mario\\mario.obj"}, "C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\textures\\marioD.bmp"));

            m_camera = new Camera();
        }

        void on_detach() override
        {
            delete m_shader;
            delete m_camera;

            for(const auto* m : m_models)
            {
                delete m;
            }
        }

        void move_camera(KeyPressEvent& a_event)
        {
            switch(a_event.get_key_code())
            {
                case 'W':
                    m_camera->move(Direction::FRONT);
                    break;
                case 'S':
                    m_camera->move(Direction::BACK);
                    break;
                case 'A':
                    m_camera->move(Direction::LEFT);
                    break;
                case 'D':
                    m_camera->move(Direction::RIGHT);
                    break;
                case 'U':
                    m_camera->move(Direction::UP);
                    break;
                case 'J':
                    m_camera->move(Direction::DOWN);
                    break;
                case 'F':
                    for(auto& m : m_models)
                    {
                        m->scale(glm::vec3(-0.01f, -0.01f, -0.01f));
                    }
                    break;
                case 'G':
                    for(auto& m : m_models)
                    {
                        m->scale(glm::vec3(0.01f, 0.01f, 0.01f));
                    }
                    break;
            }
        }

        void on_window_resize_event(WindowResizeEvent& a_event)
        {
            if(m_camera != nullptr)
            {
                m_camera->recalculate_perspective(a_event.get_width(), a_event.get_height());
                LOG_INFO("Recalculating camera perspective matrix.");
            }
        }

        void on_mouse_move_event(MouseMoveEvent& a_event)
        {
            float x_offset = (float)a_event.get_x_offset();
            float y_offset = (float)-a_event.get_y_offset();

            m_camera->recalculate_direction_vector(x_offset, y_offset);
        }
    private:
        Shader* m_shader;
        std::vector<Model*> m_models;
        Camera* m_camera;
    };
}

#endif //VISUAL_SANDBOX_H
