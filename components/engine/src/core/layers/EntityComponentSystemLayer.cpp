//
// Created by BlackFlage on 02.12.2021.
//

#include <layers/EntityComponentSystemLayer.h>
#include <optional>

#include "ImGui/imgui.h"

namespace vis
{
    MainManager* main_manager = new MainManager();

    void EntityComponentSystemLayer::on_attach()
    {
        main_manager->init();

        register_components();
        register_systems();
        set_signatures();

        m_camera = new Camera(glm::vec3(1.0f, 1.0f, 1.0f));
        m_shader = Shader::create_shader_name("vertex.glsl", "fragmentNoTex.glsl");

        Renderer::set_camera(m_camera);
        Renderer::set_shader(m_shader);
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

    void EntityComponentSystemLayer::on_imgui_render()
    {
        std::uint16_t id = main_manager->get_current_entity();

        ImGui::Begin("Properties");

        if(id != MAX_ENTITIES)
        {
            show_transform_component(id);
            show_color_component(id);
            show_mesh_component(id);
        }

        ImGui::End();

        bool show = true;
        ImGui::ShowDemoWindow(&show);
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
        m_camera->recalculate_perspective(a_event.get_width(), a_event.get_height());
    }

    void EntityComponentSystemLayer::show_transform_component(std::uint16_t a_id)
    {
        Signature sig = main_manager->get_entity_signature(a_id);

        if(sig[main_manager->get_component_type<Transform>()])
        {
            if(ImGui::CollapsingHeader("Transform")) {
                auto& transform = main_manager->get_component<Transform>(a_id);

                //Position
                ImGui::DragFloat3("Position", &transform.m_position[0], 0.1f);

                //Rotation
                ImGui::DragFloat3("Rotation", &transform.m_rotation[0]);

                //Scale
                ImGui::DragFloat3("Scale", &transform.m_scale[0], 0.01f, 0.0f);
            }
        }
    }

    void EntityComponentSystemLayer::show_color_component(std::uint16_t a_id)
    {
        Signature sig = main_manager->get_entity_signature(a_id);

        if(sig[main_manager->get_component_type<Color>()])
        {
            if(ImGui::CollapsingHeader("Color"))
            {
                auto& color = main_manager->get_component<Color>(a_id);

                ImGui::ColorEdit3("Mesh color", &color.m_color[0]);
            }
        }
    }

    void EntityComponentSystemLayer::show_mesh_component(std::uint16_t a_id)
    {
        Signature sig = main_manager->get_entity_signature(a_id);

        if(sig[main_manager->get_component_type<Mesh>()])
        {
            if(ImGui::CollapsingHeader("Mesh"))
            {
                auto& mesh = main_manager->get_component<Mesh>(a_id);

                ImGui::Text("Mesh: ");
                ImGui::SameLine();
                ImGui::Text("%s", mesh.m_name.c_str());
            }
        }
    }
}