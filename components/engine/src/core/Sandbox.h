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

namespace vis
{
    class Sandbox : public Layer
    {
    public:
        Sandbox()
        {
            std::cout << "Layer created!\n";
        }

        ~Sandbox() override { std::cout << "Layer destroyed!\n"; }

        void on_event(const Event& a_event) override
        {

        }

        void on_update() override
        {
            auto delta = Application::get_instance()->get_time_passed();

            r = std::abs(std::sin((float)delta));
            g = std::abs(std::cos((float)delta));
            b = std::abs(std::sin(0.5f + (float)delta));
        }

        void on_render() override
        {
            Renderer::change_background_color(r, g, b, 1.0f);
            CheckGLError();
            //Renderer::render(b, r, g, 0.3f, m_shader);
            Renderer::render(m_model, m_shader);
        }

        void on_attach() override
        {
            std::cout << "Layer attached!\n";
            m_shader = Shader::create_shader(R"(C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\Shaders\vertex.glsl)", R"(C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\Shaders\fragment.glsl)");
            Mesh* mesh = OBJLoader::load_from_file(R"(C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\Pulpit\Cube.obj)");
            m_model = new Model(mesh);
        }

        void on_detach() override
        {
            std::cout << "Layer detached!\n";
            delete m_shader;
            delete m_model;
        }

    private:
        float r;
        float g;
        float b;
        Shader* m_shader;
        Model* m_model;
    };
}

#endif //VISUAL_SANDBOX_H
