//
// Created by BlackFlage on 20.12.2021.
//
#include <filesystem>

#include "ResourcesLoaderLayer.h"
#include "Logger.h"

namespace vis
{
    ResourcesManager* ResourcesManager::m_instance = new ResourcesManager();

    void ResourcesLoaderLayer::on_attach()
    {
        m_resources_manager = ResourcesManager::get_instance();

        std::filesystem::path default_assets(DEFAULT_ASSETS_PATH);

        if(!std::filesystem::exists(default_assets) && !std::filesystem::is_directory(default_assets))
        {
            if(std::filesystem::create_directories(DEFAULT_ASSETS_PATH))
            {
                LOG_INFO("Directory created");
            }
        }

        m_selected_path = "";
        m_icons_zoom = 0.5f;
        m_max_items_in_row = 4;

        m_closed_dir_icon = new Texture("../engine_textures/closed_dir_icon.bmp");
        m_file_icon = new Texture("../engine_textures/file_icon.bmp");

        SceneConsole::initialize();
    }

    void ResourcesLoaderLayer::on_detach()
    {
        delete m_resources_manager;
        delete m_closed_dir_icon;
        delete m_file_icon;
    }

    void ResourcesLoaderLayer::on_event(Event &a_event)
    {

    }

    void ResourcesLoaderLayer::on_update(float a_dt)
    {

    }

    void ResourcesLoaderLayer::on_render()
    {

    }

    void ResourcesLoaderLayer::on_imgui_render()
    {
        bool show = true;
        if(ImGui::Begin("Assets browser", &show, ImGuiWindowFlags_NoTitleBar))
        {
            if(ImGui::BeginTabBar("Assets browser tabs", ImGuiTabBarFlags_None))
            {
                if(ImGui::BeginTabItem("Browser"))
                {
                    //Filesystem child
                    ImGuiTableFlags base_flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg;
                    ImGui::BeginTable("Filesystem", 2, base_flags);

                    ImGui::TableNextRow(0, ImGui::GetWindowHeight() * 0.05f);
                    ImGui::TableNextColumn();
                    if(ImGui::Button("Import"))
                    {
                        LOG_INFO("IMPORT");
                    }

                    ImGui::TableNextColumn();
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Tu cus bydzie");

                    ImGui::TableNextRow(0, ImGui::GetWindowHeight() * 0.85f);
                    ImGui::Separator();
                    ImGui::TableNextColumn();
                    std::filesystem::path root_dir(DEFAULT_ASSETS_PATH);
                    draw_dir_tree(root_dir.parent_path());

                    //Assets view child
                    ImGui::TableNextColumn();
                    std::filesystem::path assets_view_path(m_selected_path);
                    draw_files_view_table(m_selected_path);

                    ImGui::EndTable();
                    ImGui::EndTabItem();
                }
                if(ImGui::BeginTabItem("Console"))
                {
                    if(ImGui::Button("Clear"))
                    {
                        SceneConsole::get_instance()->clear();
                    }

                    ImGui::Separator();

                    SceneConsole::get_instance()->draw();

                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }

    void ResourcesLoaderLayer::draw_dir_tree(const std::filesystem::path& a_path)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

        if(std::filesystem::exists(a_path))
        {
            for(const auto& entry : std::filesystem::directory_iterator(a_path))
            {
                auto filename = entry.path().filename();

                if(entry.path().string() == m_selected_path)
                    flags |= ImGuiTreeNodeFlags_Selected;
                else
                    flags = ImGuiTreeNodeFlags_OpenOnArrow;

                if(std::filesystem::is_directory(entry.path()))
                {
                    if(ImGui::TreeNodeEx(filename.string().c_str(), flags))
                    {
                        if(ImGui::IsItemClicked())
                        {
                            m_selected_path = entry.path().string();
                        }

                        show_options_popup(filename.string());
                        draw_dir_tree(entry);

                        ImGui::TreePop();
                    }
                    else
                    {
                        show_options_popup(filename.string());
                    }
                }
            }
        }
    }

    void ResourcesLoaderLayer::draw_files_view_table(const std::filesystem::path &a_path)
    {
        if(std::filesystem::is_directory(a_path))
        {
            ImVec2 m_dimensions = ImVec2((float)m_closed_dir_icon->get_width() * m_icons_zoom, (float)m_closed_dir_icon->get_height() * m_icons_zoom);
            m_max_items_in_row = (int)(ImGui::GetColumnWidth() / m_dimensions.x);

            if(m_max_items_in_row == 0)
                m_max_items_in_row = 1;

            if(ImGui::BeginTable("Assets file view", m_max_items_in_row))
            {
                if(std::filesystem::is_empty(a_path))
                {
                    ImGui::TableNextColumn();
                    ImGui::TextWrapped("Folder is empty!");
                }
                else
                {
                    int i = 0;
                    for(const auto& entry : std::filesystem::directory_iterator(a_path))
                    {
                        if(i == m_max_items_in_row - 1)
                        {
                            i = 0;
                            ImGui::TableNextRow();
                        }

                        if(entry.is_directory())
                        {
                            std::string name = entry.path().filename().string();

                            ImGui::TableNextColumn();
                            ImGui::Image((void*)m_closed_dir_icon->get_id(),
                                         m_dimensions,
                                         ImVec2(0.0f, 0.0f),
                                         ImVec2(1.0f, 1.0f),
                                         ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                                         ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() - ImGui::CalcTextSize(name.c_str()).x) / 2.0f);
                            ImGui::TextWrapped("%s", name.c_str());
                        }
                        else if(entry.is_regular_file())
                        {
                            std::string name = entry.path().filename().string();

                            ImGui::TableNextColumn();
                            ImGui::Image((void*)m_file_icon->get_id(),
                                         m_dimensions,
                                         ImVec2(0.0f, 0.0f),
                                         ImVec2(1.0f, 1.0f),
                                         ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                                         ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() - ImGui::CalcTextSize(name.c_str()).x) / 2.0f);
                            ImGui::Text("%s", name.c_str());
                        }

                        i++;
                    }
                }

                ImGui::EndTable();
            }
        }
    }

    void ResourcesLoaderLayer::show_options_popup(const std::string& a_current_path_name)
    {
        if(ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
            ImGui::OpenPopup(a_current_path_name.c_str(), ImGuiPopupFlags_NoOpenOverExistingPopup);

        if(ImGui::BeginPopup(a_current_path_name.c_str()))
        {
            if(ImGui::MenuItem("New"))
            {
                LOG_INFO("NEW {0}", a_current_path_name);
            }
            else if(ImGui::MenuItem("Copy"))
            {
                LOG_INFO("COPY {0}", a_current_path_name);
            }
            else if(ImGui::MenuItem("Delete"))
            {
                LOG_INFO("DELETE {0}", a_current_path_name);
            }
            else if(ImGui::MenuItem("Rename"))
            {
                LOG_INFO("RENAME {0}", a_current_path_name);
            }

            ImGui::EndPopup();
        }
    }
}