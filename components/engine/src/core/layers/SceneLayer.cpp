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
        EventDispatcher dispatcher(a_event);
    }

    void SceneLayer::on_render()
    {

    }

    void SceneLayer::on_imgui_render()
    {
        ImGui::Begin("Scene Hierarchy");

        auto& m_scene_entities = m_current_scene->get_entities();
        ImGuiTreeNodeFlags current_flags;

        auto it = m_scene_entities.begin();
        if(ImGui::TreeNode("Scene Hierarchy"))
        {
            for(std::uint16_t i = 0; i < m_scene_entities.size(); i++, it++)
            {
                current_flags = m_tree_node_flags;
                if(m_selected == i)
                {
                    current_flags |= ImGuiTreeNodeFlags_Selected;
                }


                ImGui::TreeNodeEx(main_manager->get_entity(*it).get_name().c_str(), current_flags);
                if(ImGui::IsItemClicked())
                {
                    m_selected = i;
                    main_manager->set_current_entity(*it);
                }
            }

            ImGui::TreePop();
        }

        if(ImGui::IsWindowHovered(ImGuiFocusedFlags_RootWindow) && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
            ImGui::OpenPopup("Action");
        if(ImGui::BeginPopup("Action"))
        {
            ImGui::MenuItem("Menu items", NULL, false, false);
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
};