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

        ImVec2 size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight() / 2.0f);
        ImGui::BeginChild("hierarchy_child", size, true);
        auto& m_scene_entities = m_current_scene->get_entities();
        auto m_end = m_current_scene->get_entities().end();
        ImGuiTreeNodeFlags current_flags;

        std::uint16_t i = 0;
        if(ImGui::TreeNode("Scene Hierarchy"))
        {
            for(auto it = m_scene_entities.begin(); it != m_end; i++, it++)
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

                if(ImGui::BeginPopupContextItem())
                {
                    ImGui::MenuItem("Copy");
                    if(ImGui::MenuItem("Delete"))
                    {
                        remove_entity(*it);

                        it = m_current_scene->get_entities().begin();
                        m_end = m_current_scene->get_entities().end();
                        i--;
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::TreePop();
        }

        ImGui::EndChild();


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
};