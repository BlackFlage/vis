//
// Created by BlackFlage on 03.12.2021.
//

#include "ImGuiLayer.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Application.h"

namespace vis
{

    void ImGuiLayer::on_attach()
    {
        const char* glsl_version = "#version 330 core";

        IMGUI_CHECKVERSION();
        ImGuiContext* im_gui_context = ImGui::CreateContext();
        ImGui::SetCurrentContext(im_gui_context);

        ImGui::StyleColorsDark();

        ImGui_ImplOpenGL3_Init(glsl_version);

        RECT client_area = Application::get_window_instance()->get_client_rect();

        ImGuiIO& imgui_io = ImGui::GetIO();
        imgui_io.DisplaySize = ImVec2(client_area.right, client_area.bottom);
    }

    void ImGuiLayer::on_detach()
    {
        ImGui_ImplOpenGL3_Shutdown();
    }

    void ImGuiLayer::on_event(Event &a_event)
    {

    }

    void ImGuiLayer::on_update(float a_delta_time)
    {

    }

    void ImGuiLayer::on_render()
    {

    }

    void ImGuiLayer::on_imgui_render()
    {

    }
}