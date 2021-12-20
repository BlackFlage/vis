//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_RESOURCESLOADERLAYER_H
#define MAIN_RESOURCESLOADERLAYER_H

#include "Layer.h"
#include "resource_loaders/ResourcesManager.h"

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
        void on_key_press_event(KeyPressEvent& a_event);
    private:
        ResourcesManager* m_resources_manager;
    };
}


#endif //MAIN_RESOURCESLOADERLAYER_H
