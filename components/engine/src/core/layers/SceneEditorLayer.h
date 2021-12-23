//
// Created by BlackFlage on 23.12.2021.
//

#ifndef MAIN_SCENEEDITORLAYER_H
#define MAIN_SCENEEDITORLAYER_H

#include "Layer.h"

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
    };
}

#endif //MAIN_SCENEEDITORLAYER_H
