//
// Created by BlackFlage on 17.12.2021.
//

#ifndef MAIN_SCENELAYER_H
#define MAIN_SCENELAYER_H

#include "Layer.h"
#include <cstdint>

#include "scene/SceneManager.h"
#include "ImGui/imgui.h"

namespace vis
{
    class SceneLayer : public Layer
    {
    public:
        SceneLayer() = default;
        ~SceneLayer() = default;

        void on_attach() override;
        void on_detach() override;

        void on_update(float a_dt) override;
        void on_event(Event& a_event) override;
        void on_render() override;
        void on_imgui_render() override;
    private:
        void draw_scene_hierarchy();
        void on_entity_created();
        void draw_menu_popup();

        void copy(std::uint16_t a_id);
        void paste();
        void rename();
        void delete_entity(std::uint16_t a_id);
    private:
        std::unique_ptr<SceneManager> m_scene_manager;
        Scene* m_current_scene;
        std::uint16_t m_selected;
        std::uint16_t m_id_to_perform_action;

        ImVec2 m_scene_hierarchy_size;
        ImGuiTreeNodeFlags m_tree_node_flags;
        bool m_entity_clicked;
    };
}

#endif //MAIN_SCENELAYER_H
