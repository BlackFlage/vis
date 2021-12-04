//
// Created by BlackFlage on 03.12.2021.
//

#ifndef MAIN_IMGUILAYER_H
#define MAIN_IMGUILAYER_H

#include "Layer.h"
#include "ImGui/imgui.h"

namespace vis
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() = default;
        ~ImGuiLayer() override = default;
        void on_attach() override;
        void on_detach() override;

        void on_event(Event& a_event) override;
        void on_update(float a_delta_time) override;
        void on_render() override;
        void on_imgui_render() override;
    };
}

#endif //MAIN_IMGUILAYER_H
