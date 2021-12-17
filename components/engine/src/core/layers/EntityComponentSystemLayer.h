//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_ENTITYCOMPONENTSYSTEMLAYER_H
#define MAIN_ENTITYCOMPONENTSYSTEMLAYER_H

#include <memory>
#include <array>

#include "Layer.h"
#include "ecs/MainManager.h"
#include "ecs/components/BasicComponents.h"
#include "ecs/systems/BasicSystems.h"
#include "OBJLoader.h"
#include "Camera.h"
#include "Shader.h"

namespace vis
{
    class EntityComponentSystemLayer : public Layer
    {
    public:
        EntityComponentSystemLayer() = default;
        ~EntityComponentSystemLayer() override = default;

        void on_attach() override;
        void on_detach() override;
        void on_event(Event &a_event) override;
        void on_update(float a_delta_time) override;
        void on_render() override;
        void on_imgui_render() override;

    private:
        void on_mouse_move_event(MouseMoveEvent& a_event);
        void on_window_resize_event(WindowResizeEvent& a_event);

        void register_components();
        void register_systems();
        void set_signatures();

        //ImGui components pulling
        void show_transform_component(const Entity& a_entity);
        void show_color_component(const Entity& a_entity);
        void show_mesh_component(const Entity& a_entity);
    private:
        static MainManager* m_main_manager;

        std::shared_ptr<PhysicsSystem> m_physics_system;
        std::shared_ptr<RendererSystem> m_renderer_system;
        std::shared_ptr<EntityTrackSystem> m_entity_track_system;

        Shader* m_shader;
        Camera* m_camera;
    };
}

#endif //MAIN_ENTITYCOMPONENTSYSTEMLAYER_H
