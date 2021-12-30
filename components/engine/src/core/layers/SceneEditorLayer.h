//
// Created by BlackFlage on 23.12.2021.
//

#ifndef MAIN_SCENEEDITORLAYER_H
#define MAIN_SCENEEDITORLAYER_H

#define DEFAULT_ASSETS_PATH "..\\res\\assets"

#include <filesystem>
#include <stack>

#include "Layer.h"
#include "ecs/MainManager.h"
#include "ecs/systems/BasicSystems.h"
#include "ecs/components/BasicComponents.h"
#include "scene/SceneManager.h"
#include "Camera.h"
#include "Texture.h"

namespace vis
{
    class SceneEditorLayer : public Layer
    {
    public:
        void on_attach() override;
        void on_detach() override;

        void on_event(Event& a_event) override;
        void on_update(float a_dt) override;
        void on_render() override;
        void on_imgui_render() override;
    private:
        //ECS rendering, adding and initialization
        void initialize_ecs_system();
        void render_mesh_component(std::uint16_t a_id);
        void render_transform_component(std::uint16_t a_id);
        void render_color_component(std::uint16_t a_id);
        void render_add_component_button(std::uint16_t a_id);
        void add_component_to_entity(std::uint16_t a_id, const char* a_component_name);
        void render_imgui_ecs_window();

        //Scene hierarchy
        void initialize_scene_hierarchy();
        void render_scene_hierarchy();
        void render_hierarchy_popup();
        void rename_entity();
        void copy_entity();
        void paste_entity();
        void delete_entity(std::uint16_t a_id);

        //Assets panel
        void initialize_assets_panel();
        void render_assets_panel();
        void load_icons();
        void render_dir_tree(const std::filesystem::path& a_path);
        void render_entry(const std::filesystem::directory_entry& a_entry, const ImVec2& a_icon_dimensions);
        void render_files_view_table(const std::filesystem::path& a_path);
        void render_assets_popup(const std::filesystem::directory_entry& a_entry);
        void render_directories_buttons();
        void set_path_from_buttons(std::filesystem::path& path_to_set, const std::vector<std::string>& a_to_set_from, std::uint8_t a_index);
        GLuint get_icon_texture_id(const std::filesystem::directory_entry& a_entry);

        void on_window_resize_event(WindowResizeEvent& a_event);
    private:
        std::shared_ptr<PhysicsSystem>   m_physics_system;
        std::shared_ptr<RendererSystem>  m_renderer_system;
        std::unique_ptr<SceneManager>    m_scene_manager;
        std::vector<const char*>         m_components_names;

        Camera*                          m_editor_camera;
        Shader*                          m_editor_shader;
        std::string                      m_default_mesh_path;
        std::uint16_t                    m_selected_entity;
        std::uint16_t                    m_id_to_perform_action;

        std::unordered_map<std::string, Texture*> m_icons;
        float                            m_mini_icon_zoom;
        float                            m_spacing;
        ImVec2                           m_default_icon_size;
        std::uint8_t                     m_max_items_in_row;
        std::filesystem::path            m_renamed_path;
        std::filesystem::path            m_selected_path;
        std::filesystem::path            m_assets_path;

        ImGuiTreeNodeFlags               m_scene_hierarchy_flags;
    };
}

#endif //MAIN_SCENEEDITORLAYER_H
