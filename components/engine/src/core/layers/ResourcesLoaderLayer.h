//
// Created by BlackFlage on 20.12.2021.
//
#ifndef MAIN_RESOURCESLOADERLAYER_H
#define MAIN_RESOURCESLOADERLAYER_H

#define DEFAULT_ASSETS_PATH "../res/assets"

#include <memory>
#include <filesystem>

#include "Layer.h"
#include "ImGui/imgui.h"
#include "resource_loaders/ResourcesManager.h"
#include "Texture.h"

namespace vis
{
    class ResourcesLoaderLayer : public Layer
    {
    public:
        ResourcesLoaderLayer() = default;
        ~ResourcesLoaderLayer() override = default;

        void on_attach() override;
        void on_detach() override;

        void on_event(Event& a_event) override;
        void on_update(float a_dt) override;
        void on_render() override;
        void on_imgui_render() override;
    private:
        void draw_dir_tree(const std::filesystem::path& a_path);
        void draw_files_view_table(const std::filesystem::path& a_path);
        void show_options_popup(const std::string& a_current_path_name);

        void load_icons();
        GLuint get_icon_texture_id(const std::filesystem::directory_entry& a_entry);
    private:
        ResourcesManager* m_resources_manager;

        int               m_max_items_in_row;
        float             m_icon_zoom;
        float             m_mini_icon_zoom;
        std::string       m_selected_path;
        ImVec2            m_default_icon_size;
        std::unordered_map<const char*, std::unique_ptr<Texture>> m_icons;
    };
}


#endif //MAIN_RESOURCESLOADERLAYER_H
