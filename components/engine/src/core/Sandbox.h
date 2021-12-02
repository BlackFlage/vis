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
            m_model = nullptr;
        }

        ~Sandbox() override
        {

        }

        void on_event(Event& a_event) override
        {
            EventDispatcher dispatcher(a_event);
            dispatcher.dispatch<WindowResizeEvent>([this](auto&& event) { on_window_resize_event(std::forward<decltype(event)>(event)); });
            dispatcher.dispatch<MouseMoveEvent>([this](auto&& event) { on_mouse_move_event(std::forward<decltype(event)>(event)); });
        }

        void on_update(float a_delta_time) override
        {
            if(GetKeyState('A') & 0x8000)
            {
                m_camera->move(Direction::LEFT, a_delta_time);
            }
            if(GetKeyState('D') & 0x8000)
            {
                m_camera->move(Direction::RIGHT, a_delta_time);
            }
            if(GetKeyState('W') & 0x8000)
            {
                m_camera->move(Direction::FRONT, a_delta_time);
            }
            if(GetKeyState('S') & 0x8000)
            {
                m_camera->move(Direction::BACK, a_delta_time);
            }
            if(GetKeyState('U') & 0x8000)
            {
                m_camera->move(Direction::UP, a_delta_time);
            }
            if(GetKeyState('J') & 0x8000)
            {
                m_camera->move(Direction::DOWN, a_delta_time);
            }
            if(GetKeyState('F') & 0x8000)
            {
                m_model->scale(glm::vec3(-0.1f, -0.1f, -0.1f) * a_delta_time);
            }
            if(GetKeyState('G') & 0x8000)
            {
                m_model->scale(glm::vec3(0.1f, 0.1f, 0.1f) * a_delta_time);
            }
        }

        void on_render() override
        {
            Renderer::change_background_color(0.0f, 0.0f, 0.0f, 1.0f);
            Renderer::render(m_model, m_camera, m_shader);
        }

        void on_attach() override
        {
            m_shader = Shader::create_shader_name("vertex.glsl", "fragment.glsl");
            m_camera = new Camera();
            m_model = new Model({"mario\\mario.obj"},
                                 "C:\\Users\\BlackFlage\\OneDrive - Politechnika Wroclawska\\C++\\visual\\components\\engine\\res\\textures\\marioD.bmp");
        }

        void on_detach() override
        {
            delete m_shader;
            delete m_camera;
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
        Camera* m_camera;
        Model* m_model;
    };
}

#endif //VISUAL_SANDBOX_H
