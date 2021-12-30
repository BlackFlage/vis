//
// Created by BlackFlage on 23.12.2021.
//

#include "SceneEditorLayer.h"
#include "Application.h"

namespace vis
{
    std::shared_ptr<MainManager> MainManager::m_instance;

    void SceneEditorLayer::on_attach()
    {
        initialize_ecs_system();
        initialize_scene_hierarchy();
        initialize_assets_panel();

        m_editor_camera = new Camera(glm::vec3(-5.0f, 5.0f, 10.0f));
        m_editor_shader = Shader::create_shader(R"(..\engine_assets\shaders\vertex.glsl)", R"(..\engine_assets\shaders\fragmentNoTex.glsl)");
        m_default_mesh_path = R"(..\engine_assets\meshes\)";

        Renderer::set_camera(m_editor_camera);
        Renderer::set_shader(m_editor_shader);
    }

    void SceneEditorLayer::on_detach()
    {
        for(auto it = m_icons.begin(); it != m_icons.end(); it++)
        {
            delete it->second;
        }
    }

    void SceneEditorLayer::on_event(vis::Event &a_event)
    {
        EventDispatcher dispatcher(a_event);
        dispatcher.dispatch<WindowResizeEvent>([this](auto&& event){ on_window_resize_event(std::forward<decltype(event)>(event)); });
    }

    void SceneEditorLayer::on_update(float a_dt)
    {
        m_physics_system->on_update(a_dt);
    }

    void SceneEditorLayer::on_render()
    {
        m_renderer_system->on_render();
    }

    void SceneEditorLayer::on_imgui_render()
    {
        render_imgui_ecs_window();
        render_scene_hierarchy();
        render_assets_panel();

        bool open = true;
        ImGui::Begin("Scene viewport", &open, ImGuiWindowFlags_NoBackground);

        ImVec2 dimensions = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
        ImGui::Image((void*)Application::get_instance()->get_framebuffer_texture_id(), dimensions);

        ImGui::End();

    }

    void SceneEditorLayer::initialize_ecs_system()
    {
        MainManager::init();

        //Register all available components
        MainManager::get_instance()->register_component<Transform>();
        MainManager::get_instance()->register_component<Color>();
        MainManager::get_instance()->register_component<RigidBody>();
        MainManager::get_instance()->register_component<MeshComponent>();

        //Register all system
        m_physics_system = MainManager::get_instance()->register_system<PhysicsSystem>();
        m_renderer_system = MainManager::get_instance()->register_system<RendererSystem>();

        //Set system signatures
        Signature phys_signature;
        phys_signature.set(MainManager::get_instance()->get_component_type<Transform>(), true);
        phys_signature.set(MainManager::get_instance()->get_component_type<RigidBody>(), true);
        MainManager::get_instance()->set_system_signature<PhysicsSystem>(phys_signature);

        Signature rend_signature;
        rend_signature.set(MainManager::get_instance()->get_component_type<MeshComponent>(), true);
        rend_signature.set(MainManager::get_instance()->get_component_type<Color>(), true);
        rend_signature.set(MainManager::get_instance()->get_component_type<Transform>(), true);
        MainManager::get_instance()->set_system_signature<RendererSystem>(rend_signature);

        m_components_names = {"Transform", "Color", "Mesh", "RigidBody", "Camera"};
    }

    void SceneEditorLayer::render_transform_component(std::uint16_t a_id)
    {
        Signature sig = MainManager::get_instance()->get_entity_signature(a_id);

        if(sig[MainManager::get_instance()->get_component_type<Transform>()])
        {
            if(ImGui::CollapsingHeader("Transform")) {
                auto& transform = MainManager::get_instance()->get_component<Transform>(a_id);

                ImGui::DragFloat3("Position", &transform.m_position[0], 0.1f);

                ImGui::DragFloat3("Rotation", &transform.m_rotation[0]);

                ImGui::DragFloat3("Scale", &transform.m_scale[0], 0.01f, 0.0f);
            }
        }
    }

    void SceneEditorLayer::render_mesh_component(std::uint16_t a_id)
    {
        Signature sig = MainManager::get_instance()->get_entity_signature(a_id);

        if(sig[MainManager::get_instance()->get_component_type<Color>()])
        {
            if(ImGui::CollapsingHeader("Color"))
            {
                auto& color = MainManager::get_instance()->get_component<Color>(a_id);

                ImGui::ColorEdit3("Mesh color", &color.m_color[0]);
            }
        }
    }

    void SceneEditorLayer::render_color_component(std::uint16_t a_id)
    {
        Signature sig = MainManager::get_instance()->get_entity_signature(a_id);

        if(sig[MainManager::get_instance()->get_component_type<MeshComponent>()])
        {
            if(ImGui::CollapsingHeader("Mesh"))
            {
                auto mesh_id = MainManager::get_instance()->get_component<MeshComponent>(a_id).m_id;
                auto mesh = ResourcesManager::get_instance()->get_mesh(mesh_id);

                ImGui::Text("Mesh id: %d", mesh_id);
                ImGui::Text("Vertices: %d", (int)mesh->get_vertices().size());
                ImGui::Text("Indices: %d", (int)mesh->get_indices().size());
            }
        }
    }

    void SceneEditorLayer::render_add_component_button(std::uint16_t a_id)
    {
        ImVec2 button_size = ImVec2(-FLT_MIN, ImGui::GetWindowHeight() * 0.025f);

        if(ImGui::Button("Add Component", button_size))
            ImGui::OpenPopup("Components list");

        if(ImGui::BeginPopup("Components list"))
        {
            for(auto & m_components_name : m_components_names)
            {
                if(ImGui::MenuItem(m_components_name))
                {
                    add_component_to_entity(a_id, m_components_name);
                }
            }

            ImGui::EndPopup();
        }
    }

    void SceneEditorLayer::add_component_to_entity(std::uint16_t a_id, const char *a_component_name)
    {
        if(std::strcmp(a_component_name, "Transform") == 0)
        {
            MainManager::get_instance()->add_component(a_id, Transform{
                    .m_position = glm::vec3(0.0f),
                    .m_rotation = glm::vec3(1.0f),
                    .m_scale = glm::vec3(1.0f)
            });
        }
        else if(std::strcmp(a_component_name, "Color") == 0)
        {
            MainManager::get_instance()->add_component(a_id, Color{ .m_color = glm::vec3(0.3f) });
        }
        else if(std::strcmp(a_component_name, "Mesh") == 0)
        {
            MeshComponent mesh_comp = {.m_id = ResourcesManager::get_instance()->load_mesh(m_default_mesh_path + "cube.obj")};

            if(mesh_comp.m_id != MAX_COMPONENTS)
            {
                MainManager::get_instance()->add_component(a_id, mesh_comp);
            }
        }
        else if(std::strcmp(a_component_name, "RigidBody") == 0)
        {
            MainManager::get_instance()->add_component(a_id, RigidBody{ .vel_x = 0.0f, .vel_y = 0.0f, .vel_z = 0.0f});
        }
    }

    void SceneEditorLayer::on_window_resize_event(WindowResizeEvent &a_event)
    {
        m_editor_camera->recalculate_perspective(a_event.get_width(), a_event.get_height());
    }

    void SceneEditorLayer::render_imgui_ecs_window()
    {
        std::uint16_t id = MainManager::get_instance()->get_current_entity();

        ImGui::Begin("Properties");

        if(id != MAX_ENTITIES)
        {
            render_transform_component(id);
            render_color_component(id);
            render_mesh_component(id);

            render_add_component_button(id);
        }

        ImGui::End();

        //Gonna be deleted soon
        bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void SceneEditorLayer::initialize_scene_hierarchy()
    {
        m_scene_manager = std::make_unique<SceneManager>();
        m_scene_hierarchy_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        m_selected_entity = MAX_ENTITIES;
        m_id_to_perform_action = MAX_ENTITIES;
    }

    void SceneEditorLayer::render_scene_hierarchy()
    {
        ImGui::Begin("Scene Hierarchy");
        bool selected = false;
        ImGuiTreeNodeFlags flags = m_scene_hierarchy_flags;
        std::uint16_t i = 0;

        if(ImGui::TreeNode(m_scene_manager->get_current_scene()->get_name().c_str()))
        {
            auto &m_scene_entities = m_scene_manager->get_current_scene()->get_entities();
            for (auto it = m_scene_entities.begin(); it != m_scene_entities.end(); it++, i++) {
                if (m_selected_entity == i) {
                    selected = true;
                    MainManager::get_instance()->set_current_entity(*it);
                } else
                    selected = false;

                if (ImGui::Selectable(MainManager::get_instance()->get_entity(*it).get_name().c_str(), selected)) {
                    m_selected_entity = i;
                    m_id_to_perform_action = MAX_ENTITIES;
                }
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
                    m_id_to_perform_action = *it;
                }
            }

            ImGui::TreePop();
        }

        render_hierarchy_popup();

        ImGui::End();
    }

    void SceneEditorLayer::render_hierarchy_popup()
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
                    m_scene_manager->get_current_scene()->add_entity(EntityType::EMPTY);
                }
                if(ImGui::MenuItem("Cube"))
                {
                    m_scene_manager->get_current_scene()->add_entity(EntityType::CUBE);
                }
                if(ImGui::MenuItem("Sphere"))
                {
                    m_scene_manager->get_current_scene()->add_entity(EntityType::SPHERE);
                }

                ImGui::EndMenu();
            }

            ImGui::EndPopup();
        }
    }

    void SceneEditorLayer::rename_entity()
    {
        LOG_INFO("RENAME ENTITY");
    }

    void SceneEditorLayer::copy_entity()
    {
        LOG_INFO("COPY ENTITY");
    }

    void SceneEditorLayer::paste_entity()
    {
        LOG_INFO("PASTE ENTITY");
    }

    void SceneEditorLayer::delete_entity(std::uint16_t a_id)
    {
        if(a_id != MAX_ENTITIES)
        {
            m_scene_manager->get_current_scene()->remove_entity(a_id);
            MainManager::get_instance()->destroy_entity(a_id);
            MainManager::get_instance()->set_current_entity(MAX_ENTITIES);
            m_id_to_perform_action = MAX_ENTITIES;
            m_selected_entity = MAX_ENTITIES;
        }
    }

    void SceneEditorLayer::initialize_assets_panel()
    {

        m_max_items_in_row = 6;
        m_selected_path = "";
        m_default_icon_size = ImVec2(64, 64);
        m_mini_icon_zoom = 0.25f;
        m_renamed_path = "";

        std::filesystem::path default_assets(DEFAULT_ASSETS_PATH);

        if(!std::filesystem::exists(default_assets) && !std::filesystem::is_directory(default_assets))
        {
            std::filesystem::create_directories(default_assets);
        }

        load_icons();
    }

    void SceneEditorLayer::render_assets_panel()
    {
        bool show = true;
        if(ImGui::Begin("Assets browser", &show, ImGuiWindowFlags_NoTitleBar))
        {
            if(ImGui::BeginTabBar("Assets browser tabs", ImGuiTabBarFlags_None))
            {
                if(ImGui::BeginTabItem("Browser"))
                {
                    //Filesystem child
                    ImGui::BeginTable("Filesystem", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_RowBg);

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
                    render_dir_tree(root_dir.parent_path());

                    //Assets view child
                    ImGui::TableNextColumn();
                    std::filesystem::path assets_view_path(m_selected_path);
                    render_files_view_table(m_selected_path);

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

    void SceneEditorLayer::load_icons()
    {
        m_icons.insert({"closed_dir", new Texture(R"(..\engine_assets\textures\closed_folder_icon.png)")});
        m_icons.insert({"opened_dir", new Texture(R"(..\engine_assets\textures\opened_folder_icon.png)")});
        m_icons.insert({"full_dir", new Texture(R"(..\engine_assets\textures\full_folder_icon.png)")});
        m_icons.insert({"default", new Texture(R"(..\engine_assets\textures\file_icon.png)")});
    }

    void SceneEditorLayer::render_dir_tree(const std::filesystem::path &a_path)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
        ImVec2 icon_dimensions = ImVec2(m_default_icon_size.x * m_mini_icon_zoom, m_default_icon_size.y * m_mini_icon_zoom);

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
                    Texture* current_tex = m_icons.at("closed_dir");

                    if(current_tex)
                    {
                        ImGui::Image((void*)current_tex->get_id(), icon_dimensions, (ImVec2 &&) current_tex->get_uv0(),(ImVec2 &&) current_tex->get_uv1());
                        ImGui::SameLine();
                    }

                    if(entry.path() != m_renamed_path)
                    {
                        if(ImGui::TreeNodeEx(filename.string().c_str(), flags))
                        {
                            if(ImGui::IsItemClicked())
                            {
                                m_selected_path = entry.path().string();
                            }

                            render_assets_popup(entry);
                            render_dir_tree(entry);

                            ImGui::TreePop();
                        }
                        else
                        {
                            render_assets_popup(entry);
                        }
                    }
                    else
                    {
                        LOG_INFO("Renaming will be here");
                    }
                }
            }
        }
    }

    void SceneEditorLayer::render_files_view_table(const std::filesystem::path &a_path)
    {
        if(std::filesystem::is_directory(a_path))
        {
            ImVec2 m_dimensions = ImVec2(m_default_icon_size.x, m_default_icon_size.y);
            m_max_items_in_row = (int)(ImGui::GetColumnWidth() / m_default_icon_size.x);

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

                        std::string name = entry.path().filename().string();
                        ImGui::TableNextColumn();
                        ImGui::Image((void*)get_icon_texture_id(entry),
                                     m_dimensions,
                                     ImVec2(0.0f, 0.0f),
                                     ImVec2(1.0f, 1.0f),
                                     ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                                     ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetColumnWidth() - ImGui::CalcTextSize(name.c_str()).x) / 2.0f);
                        ImGui::TextWrapped("%s", name.c_str());

                        i++;
                    }
                }

                ImGui::EndTable();
            }
        }
    }

    void SceneEditorLayer::render_assets_popup(const std::filesystem::directory_entry &a_entry)
    {
        if(ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
            ImGui::OpenPopup(a_entry.path().string().c_str(), ImGuiPopupFlags_NoOpenOverExistingPopup);

        if(ImGui::BeginPopup(a_entry.path().string().c_str()))
        {
            if(ImGui::MenuItem("New"))
            {
                auto new_path = a_entry.path();
                new_path /= "New folder";

                int next_id = 0;
                while(!std::filesystem::create_directory(new_path))
                {
                    new_path = new_path.parent_path();
                    new_path /= "New folder";
                    new_path += "(" + std::to_string(next_id) + ")";
                    next_id++;
                }
            }
            else if(ImGui::MenuItem("Delete"))
            {
                std::filesystem::remove_all(a_entry.path());
            }
            else if(ImGui::MenuItem("Rename"))
            {
                LOG_INFO("Rename {0}", a_entry.path().filename().string().c_str());
            }

            ImGui::EndPopup();
        }
    }

    GLuint SceneEditorLayer::get_icon_texture_id(const std::filesystem::directory_entry &a_entry)
    {
        if(a_entry.is_directory())
        {
            if(std::filesystem::is_empty(a_entry.path()))
                return m_icons.at("closed_dir")->get_id();
            else
                return m_icons.at("full_dir")->get_id();
        }
        else
        {
            std::string extension = a_entry.path().extension().string();

            if(m_icons.find(extension) != m_icons.end())
                return m_icons.at(extension)->get_id();
            else
                return m_icons.at("default")->get_id();
        }
    }
}
