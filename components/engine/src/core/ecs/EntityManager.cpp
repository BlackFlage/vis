//
// Created by BlackFlage on 02.12.2021.
//

#include "EntityManager.h"
#include "Logger.h"

namespace vis
{

    void EntityManager::init()
    {
        m_available_entities = std::queue<Entity>();
        m_signatures = std::array<Signature, MAX_ENTITIES>();
        m_living_entities = 0;

        for(Entity entity = 0; entity < MAX_ENTITIES; entity++)
        {
            m_available_entities.push(entity);
        }
    }

    Entity EntityManager::create_entity()
    {
        if(m_living_entities >= MAX_ENTITIES)
        {
            LOG_ERROR("Maximum entities count reached!");
            return 0;
        }

        Entity entity = m_available_entities.front();
        m_available_entities.pop();
        m_living_entities++;

        return entity;
    }

    void EntityManager::on_entity_destroyed(const Entity &a_entity)
    {
        if(a_entity <= 0 || a_entity > MAX_ENTITIES)
        {
            LOG_ERROR("Can't destroy entity! Passed ID out of range.");
            return;
        }

        m_available_entities.push(a_entity);
        m_signatures[a_entity].reset();
        m_living_entities--;
    }

    Signature EntityManager::get_signature(const Entity &a_entity)
    {
        if(a_entity <= 0 || a_entity > MAX_ENTITIES)
        {
            LOG_ERROR("Can't get entity signature! Passed ID out of range.");
            return {};
        }

        return m_signatures[a_entity];
    }

    void EntityManager::set_signature(const Entity &a_entity, const Signature &a_signature)
    {
        if(a_entity <= 0 || a_entity > MAX_ENTITIES)
        {
            LOG_ERROR("Can't set entity signature! Passed ID out of range.");
            return;
        }

        m_signatures[a_entity] = a_signature;
    }
}