//
// Created by BlackFlage on 02.12.2021.
//

#include <EntityComponentSystemLayer.h>

namespace vis
{
    void EntityComponentSystemLayer::on_attach()
    {
        m_entity_manager = std::make_unique<EntityManager>();
        m_entity_manager->init();

        m_component_manager = std::make_unique<ComponentManager>();
        m_component_manager->init();

        m_system_manager = std::make_unique<SystemManager>();
        m_system_manager->init();
    }

    void EntityComponentSystemLayer::on_detach()
    {

    }

    void EntityComponentSystemLayer::on_event(Event &a_event)
    {

    }

    void EntityComponentSystemLayer::on_update(float a_delta_time)
    {

    }

    void EntityComponentSystemLayer::on_render()
    {

    }
}