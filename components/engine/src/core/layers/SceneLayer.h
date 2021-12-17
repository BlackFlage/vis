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
        void create_entity(KeyPressEvent& event);
        void on_entity_created();
    private:
        std::unique_ptr<SceneManager> m_scene_manager;
        Scene* m_current_scene;

        ImGuiTreeNodeFlags m_tree_node_flags;
        bool m_test_drag_and_drop;
        std::uint16_t m_selected;
    };
}

#endif //MAIN_SCENELAYER_H
