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
        m_show_demo_window = true;

        main_manager->init();

        register_components();
        register_systems();
        set_signatures();

        m_camera = new Camera();
        m_shader = Shader::create_shader_name("vertex.glsl", "fragmentNoTex.glsl");

        Renderer::set_camera(m_camera);
        Renderer::set_shader(m_shader);

        Mesh mesh = OBJLoader::load_from_models("cube//cube.obj");

        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_real_distribution<float> randPositionX(-30.0f, 30.0f);;
        std::uniform_real_distribution<float> randPositionY(-40.0f, 10.0f);
        std::uniform_real_distribution<float> randPositionZ(-40.0f, 10.0f);
        std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
        std::uniform_real_distribution<float> randSpeed(3.0f, 7.0f);

        for(int i = 0; i < 100; i++)
        {
            my_entities[i] = main_manager->create_entity();

            main_manager->add_component(my_entities[i], Transform{
                    .m_position = glm::vec3(randPositionX(generator), randPositionY(generator), randPositionZ(generator)),
                    .m_rotation = glm::vec3(0.0f),
                    .m_scale = glm::vec3(1.0f)
            });

            main_manager->add_component(my_entities[i], Color{
                .m_color = glm::vec3(randColor(generator), randColor(generator), randColor(generator))
            });

            main_manager->add_component(my_entities[i], mesh);

            main_manager->add_component(my_entities[i], RigidBody{
                                                            .vel_x = 0.0f,
                                                            .vel_y = randSpeed(rd),
                                                            .vel_z = 0.0f
            });
        }
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
        if((GetKeyState('A') & 0x8000))
        {
            m_camera->move(Direction::LEFT, a_delta_time);
        }
        if((GetKeyState('D') & 0x8000))
        {
            m_camera->move(Direction::RIGHT, a_delta_time);
        }
        if((GetKeyState('W') & 0x8000))
        {
            m_camera->move(Direction::FRONT, a_delta_time);
        }
        if((GetKeyState('S') & 0x8000))
        {
            m_camera->move(Direction::BACK, a_delta_time);
        }

        m_physics_system->on_update(a_delta_time);
        m_entity_track_system->on_update(a_delta_time);
    }

    void EntityComponentSystemLayer::on_render()
    {
        Renderer::change_background_color(0.0f, 0.0f, 0.0f, 1.0f);
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
            phys_signature.set(main_manager->get_component_type<Transform>(), 1);
            phys_signature.set(main_manager->get_component_type<RigidBody>(), 1);
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
        m_camera->recalculate_direction_vector(INPUT->get_mouse_delta_x(), INPUT->get_mouse_delta_y());
    }

    void EntityComponentSystemLayer::on_window_resize_event(WindowResizeEvent& a_event)
    {
        if(m_camera != nullptr)
        {
            m_camera->recalculate_perspective(a_event.get_width(), a_event.get_height());
            LOG_INFO("Recalculating camera perspective matrix.");
        }
    }

    void EntityComponentSystemLayer::on_imgui_render()
    {
        if(m_show_demo_window)
        {
            ImGui::ShowDemoWindow(&m_show_demo_window);
        }
    }
}