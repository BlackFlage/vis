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
        m_selected = MAX_ENTITIES;
        m_id_to_perform_action = MAX_ENTITIES;
        m_entity_clicked = false;
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

        ImGui::End();
    }

    void SceneLayer::on_entity_created()
    {

    }

    void SceneLayer::draw_scene_hierarchy()
    {
        bool selected = false;
        ImGuiTreeNodeFlags flags = m_tree_node_flags;
        std::uint16_t i = 0;

        if(ImGui::TreeNode(m_current_scene->get_name().c_str()))
        {
            auto &m_scene_entities = m_current_scene->get_entities();
            for (auto it = m_scene_entities.begin(); it != m_scene_entities.end(); it++, i++) {
                if (m_selected == i) {
                    selected = true;
                    main_manager->set_current_entity(*it);
                } else
                    selected = false;

                if (ImGui::Selectable(main_manager->get_entity(*it).get_name().c_str(), selected)) {
                    m_selected = i;
                    m_id_to_perform_action = MAX_ENTITIES;
                }
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
                    m_id_to_perform_action = *it;
                }
            }

            ImGui::TreePop();
        }

        draw_menu_popup();
    }

    void SceneLayer::draw_menu_popup()
    {
        if(ImGui::IsWindowHovered( ImGuiFocusedFlags_RootWindow)
        &&  ImGui::IsMouseReleased(ImGuiMouseButton_Right))
            ImGui::OpenPopup("Options");

        if(ImGui::BeginPopup("Options"))
        {
            if(ImGui::MenuItem("Copy"))
            {

            }
            if(ImGui::MenuItem("Paste"))
            {

            }
            if(ImGui::MenuItem("Rename"))
            {

            }
            if(ImGui::MenuItem("Delete"))
            {
                delete_entity(m_id_to_perform_action);
            }

            ImGui::Separator();

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
    }

    void SceneLayer::copy(std::uint16_t a_id)
    {
        LOG_INFO("COPY");
    }

    void SceneLayer::paste()
    {
        LOG_INFO("PASTE");
    }

    void SceneLayer::rename()
    {
        LOG_INFO("RENAME");
    }

    void SceneLayer::delete_entity(std::uint16_t a_id)
    {
        if(a_id != MAX_ENTITIES)
        {
            m_current_scene->remove_entity(a_id);
            main_manager->destroy_entity(a_id);
            main_manager->set_current_entity(MAX_ENTITIES);
            m_id_to_perform_action = MAX_ENTITIES;
            m_selected = MAX_ENTITIES;
        }
    }
}