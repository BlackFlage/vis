//
// Created by BlackFlage on 23.12.2021.
//

#include "SceneEditorLayer.h"
#include "ImGui/imgui.h"
#include "Application.h"

namespace vis
{
    void SceneEditorLayer::on_attach()
    {

    }

    void SceneEditorLayer::on_detach()
    {

    }

    void SceneEditorLayer::on_event(vis::Event &a_event)
    {

    }

    void SceneEditorLayer::on_update(float a_dt)
    {

    }

    void SceneEditorLayer::on_render()
    {

    }

    void SceneEditorLayer::on_imgui_render()
    {
        bool open = true;
        ImGui::Begin("Scene viewport", &open, ImGuiWindowFlags_NoBackground);

        ImVec2 dimensions = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
        ImGui::Image((void*)Application::get_instance()->get_framebuffer_texture_id(), dimensions);

        ImGui::End();
    }
}
