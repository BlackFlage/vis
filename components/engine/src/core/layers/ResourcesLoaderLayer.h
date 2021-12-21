//
// Created by BlackFlage on 20.12.2021.
//
#ifndef MAIN_RESOURCESLOADERLAYER_H
#define MAIN_RESOURCESLOADERLAYER_H

#define DEFAULT_ASSETS_PATH "../res/assets"

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
    private:
        ResourcesManager* m_resources_manager;
        Texture* m_closed_dir_icon;
        Texture* m_file_icon;

        std::string m_selected_path;
        float m_icons_zoom;
        int m_max_items_in_row;
    };
}


#endif //MAIN_RESOURCESLOADERLAYER_H
