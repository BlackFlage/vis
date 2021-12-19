//
// Created by BlackFlage on 17.12.2021.
//

#include "SceneLayer.h"
#include "ecs/MainManager.h"

namespace vis
{

    void vis::SceneLayer::on_attach()
    {
        m_scene_manager = std::make_unique<SceneManager>();
        m_current_scene = m_scene_manager->get_current_scene();

        m_tree_node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        m_test_drag_and_drop = false;
        m_selected = 0;
    }

    void SceneLayer::on_detach()
    {

    }

    void SceneLayer::on_update(float a_dt)
    {

    }

    void SceneLayer::on_event(Event &a_event)
    {
    }

    void SceneLayer::on_render()
    {

    }

    void SceneLayer::on_imgui_render()
    {
        ImGui::Begin("Scene Hierarchy");

        draw_scene_hierarchy();

        if(ImGui::IsWindowHovered( ImGuiFocusedFlags_RootWindow)
                                    &&  ImGui::IsMouseReleased(ImGuiMouseButton_Right))
            ImGui::OpenPopup("Action");
        if(ImGui::BeginPopup("Action"))
        {
            ImGui::MenuItem("Menu items", nullptr, false, false);
            if(ImGui::BeginMenu("3D"))
            {
                if(ImGui::MenuItem("Empty"))
                {
                    m_current_scene->add_entity(EntityType::EMPTY);
                }
                if(ImGui::MenuItem("Cube"))
                {
                    m_current_scene->add_entity(EntityType::CUBE);
                }
                if(ImGui::MenuItem("Sphere"))
                {
                    m_current_scene->add_entity(EntityType::SPHERE);
                }

                ImGui::EndMenu();
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }

    void SceneLayer::on_entity_created()
    {

    }

    void SceneLayer::remove_entity(std::uint16_t a_id)
    {
        m_current_scene->remove_entity(a_id);
        main_manager->destroy_entity(a_id);
    }

    void SceneLayer::draw_scene_hierarchy()
    {
        ImGuiTreeNodeFlags current_flags;

        auto& scene_entities = m_current_scene->get_entities();
        auto begin = scene_entities.begin();
        auto end = scene_entities.end();

        ImVec2 size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() / 2.0f);
        ImGui::BeginChild("hierarchy_child", size, true);
        if(ImGui::TreeNode("Scene Hierarchy"))
        {
            for(std::uint16_t i = 0; begin != end; i++, begin++)
            {
                current_flags = m_tree_node_flags;
                if(m_selected == i)
                {
                    current_flags |= ImGuiTreeNodeFlags_Selected;
                }

                ImGui::TreeNodeEx(main_manager->get_entity(*begin).get_name().c_str(), current_flags);
                if(ImGui::IsItemClicked())
                {
                    m_selected = i;
                    main_manager->set_current_entity(*begin);
                }

                if(ImGui::BeginPopupContextItem())
                {
                    if(ImGui::MenuItem("Copy"))
                    {

                    }

                    if(ImGui::MenuItem("Delete"))
                    {
                        remove_entity(*begin);
                        m_selected = MAX_ENTITIES;

                        main_manager->set_current_entity(MAX_ENTITIES);

                        ImGui::EndPopup();
                        ImGui::TreePop();
                        ImGui::EndChild();
                        return;
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::TreePop();
        }

        ImGui::EndChild();
    }
}