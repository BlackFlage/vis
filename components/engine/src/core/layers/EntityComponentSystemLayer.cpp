//
// Created by BlackFlage on 02.12.2021.
//

#include <layers/EntityComponentSystemLayer.h>
#include <random>
#include "ImGui/imgui.h"
#include "Application.h"

namespace vis
{
    MainManager* main_manager = new MainManager();

    void EntityComponentSystemLayer::on_attach()
    {
        main_manager->init();

        register_components();
        register_systems();
        set_signatures();
    }

    void EntityComponentSystemLayer::on_detach()
    {

    }

    void EntityComponentSystemLayer::on_event(Event &a_event)
    {
        EventDispatcher dispatcher(a_event);
        dispatcher.dispatch<WindowResizeEvent>([this](auto&& event) { on_window_resize_event(std::forward<decltype(event)>(event)); });
        dispatcher.dispatch<MouseMoveEvent>([this](auto&& event) { on_mouse_move_event(std::forward<decltype(event)>(event)); });
    }

    void EntityComponentSystemLayer::on_update(float a_delta_time)
    {
        m_physics_system->on_update(a_delta_time);
        m_entity_track_system->on_update(a_delta_time);
    }

    void EntityComponentSystemLayer::on_render()
    {
        m_renderer_system->on_render();
    }

    void EntityComponentSystemLayer::register_components()
    {
        main_manager->register_component<Transform>();
        main_manager->register_component<Color>();
        main_manager->register_component<RigidBody>();
        main_manager->register_component<Mesh>();
    }

    void EntityComponentSystemLayer::register_systems()
    {
        m_physics_system = main_manager->register_system<PhysicsSystem>();
        m_renderer_system = main_manager->register_system<RendererSystem>();
        m_entity_track_system = main_manager->register_system<EntityTrackSystem>();
    }

    void EntityComponentSystemLayer::set_signatures()
    {
        {
            Signature phys_signature;
            phys_signature.set(main_manager->get_component_type<Transform>(), true);
            phys_signature.set(main_manager->get_component_type<RigidBody>(), true);
            main_manager->set_system_signature<PhysicsSystem>(phys_signature);
        }

        {
            Signature rend_signature;
            rend_signature.set(main_manager->get_component_type<Mesh>(), true);
            rend_signature.set(main_manager->get_component_type<Color>(), true);
            rend_signature.set(main_manager->get_component_type<Transform>(), true);
            main_manager->set_system_signature<RendererSystem>(rend_signature);
        }

        {
            Signature ent_signature;
            ent_signature.set(main_manager->get_component_type<Transform>(), true);
            main_manager->set_system_signature<EntityTrackSystem>(ent_signature);
        }
    }

    void EntityComponentSystemLayer::on_mouse_move_event(MouseMoveEvent &a_event)
    {

    }

    void EntityComponentSystemLayer::on_window_resize_event(WindowResizeEvent& a_event)
    {

    }

    void EntityComponentSystemLayer::on_imgui_render()
    {

    }
}