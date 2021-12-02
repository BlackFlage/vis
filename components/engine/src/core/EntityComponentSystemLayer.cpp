//
// Created by BlackFlage on 02.12.2021.
//

#include <EntityComponentSystemLayer.h>
#include "Logger.h"

namespace vis
{

    vis::EntityComponentSystemLayer::~EntityComponentSystemLayer()
    {

    }

    void EntityComponentSystemLayer::on_attach()
    {
        m_entity_manager = std::make_unique<EntityManager>();
        m_entity_manager->init();

        m_component_manager = std::make_unique<ComponentManager>();
        m_component_manager->init();
    }

    void EntityComponentSystemLayer::on_detach()
    {

    }

    void EntityComponentSystemLayer::on_event(Event &a_event)
    {
        if(a_event.get_event_type() == EventType::KEY_PRESS)
        {
            Entity ent = m_entity_manager->create_entity();
            LOG_INFO("Entity created with ID: {0}", ent);
        }
    }

    void EntityComponentSystemLayer::on_update(float a_delta_time)
    {

    }

    void EntityComponentSystemLayer::on_render()
    {

    }
}