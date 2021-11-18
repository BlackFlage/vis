//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_SANDBOX_H
#define VISUAL_SANDBOX_H

#include "Layer.h"
#include <iostream>
#include <cmath>
#include "Input.h"
#include "Gl/gl.h"
#include "Renderer.h"
#include "OBJLoader.h"
#include "Camera.h"
#include "KeyboardEvent.h"
#include <functional>

namespace vis
{
    class Sandbox : public Layer
    {
    public:
        Sandbox()
        {

        }

        ~Sandbox() override
        {

        }

        void on_event(Event& a_event) override
        {
            EventDispatcher dispatcher(a_event);
            dispatcher.dispatch<KeyPressEvent>([this](auto && PH1) { move_camera(std::forward<decltype(PH1)>(PH1)); });
        }

        void on_update() override
        {

        }

        void on_render() override
        {
            Renderer::change_background_color(1.0f, 1.0f, 1.0f, 1.0f);

            for(const auto& m : m_models)
            {
                Renderer::render(m, m_camera, m_shader);
            }
            glm::vec3 pos = m_camera->get_position();
            LOG_INFO("CAMERA POS: {0} {1} {2}", pos.x, pos.y, pos.z);
        }

        void on_attach() override
        {
            m_shader = Shader::create_shader(R"(C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\Shaders\vertex.glsl)", R"(C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\Shaders\fragment.glsl)");
            Mesh* mesh = OBJLoader::load_from_file(R"(C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\Pulpit\Flashlight.obj)");
            m_models.push_back(new Model(mesh));

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
                    m_camera->translate(glm::vec3(0.0f, 0.0f, 0.1f));
                    break;
                case 'S':
                    m_camera->translate(glm::vec3(0.0f, 0.0f, -0.1f));
                    break;
                case 'A':
                    m_camera->translate(glm::vec3(0.1f, 0.0f, 0.0f));
                    break;
                case 'D':
                    m_camera->translate(glm::vec3(-0.1f, 0.0f, 0.0f));
                    break;
                case 'U':
                    m_camera->translate(glm::vec3(0.0f, -0.1f, 0.0f));
                    break;
                case 'J':
                    m_camera->translate(glm::vec3(0.0f, 0.1f, 0.0f));
                    break;

            }
        }

    private:
        Shader* m_shader;
        std::vector<Model*> m_models;
        Camera* m_camera;
    };
}

#endif //VISUAL_SANDBOX_H
