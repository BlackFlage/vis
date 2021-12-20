//
// Created by BlackFlage on 07.10.2021.
//

#ifndef VISUAL_SANDBOX_H
#define VISUAL_SANDBOX_H

#include "Layer.h"
#include <iostream>
#include <cmath>
#include "gl/GL.h"
#include "Renderer.h"
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

        }

        ~Sandbox() override
        {

        }

        void on_event(Event& a_event) override
        {
            EventDispatcher dispatcher(a_event);
        }

        void on_update(float a_delta_time) override
        {

        }

        void on_render() override
        {

        }

        void on_attach() override
        {

        }

        void on_detach() override
        {

        }

        void on_imgui_render() override
        {

        }
    };
}

#endif //VISUAL_SANDBOX_H
