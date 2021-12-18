//
// Created by BlackFlage on 02.12.2021.
//

#include "EntityManager.h"
#include "Logger.h"

namespace vis
{

    void EntityManager::init()
    {
        m_available_entities = std::queue<std::uint16_t>();
        m_signatures = std::array<Signature, MAX_ENTITIES>();
        m_living_entities = 0;

        for(std::uint16_t i = 0; i < MAX_ENTITIES; i++)
        {
            m_available_entities.push(i);
        }
    }

    std::uint16_t EntityManager::create_entity()
    {
        if(m_living_entities >= MAX_ENTITIES)
        {
            LOG_ERROR("Maximum entities count reached!");
            return MAX_ENTITIES;
        }

        std::uint16_t id = m_available_entities.front();
        m_entities.insert({id, Entity(id)});
        m_available_entities.pop();
        m_living_entities++;

        return id;
    }

    Entity EntityManager::get_entity(std::uint16_t a_id)
    {
        if(m_entities.find(a_id) == m_entities.end())
        {
            LOG_ERROR("Trying to access non existing entity");
            return {MAX_ENTITIES};
        }

        return m_entities.at(a_id);
    }

    void EntityManager::on_entity_destroyed(std::uint16_t a_id)
    {
        if(a_id <= 0 || a_id > MAX_ENTITIES)
        {
            LOG_ERROR("Can't destroy entity! Passed ID out of range.");
            return;
        }

        m_available_entities.push(a_id);
        m_entities.erase(a_id);
        m_signatures[a_id].reset();
        m_living_entities--;
    }

    Signature EntityManager::get_signature(std::uint16_t a_id)
    {
        if(a_id < 0 || a_id > MAX_ENTITIES)
        {
            LOG_ERROR("Can't get entity signature! Passed ID out of range.");
            return {};
        }

        return m_signatures[a_id];
    }

    void EntityManager::set_signature(std::uint16_t a_id, Signature& a_signature)
    {
        if(a_id < 0 || a_id > MAX_ENTITIES)
        {
            LOG_ERROR("Can't set entity signature! Passed ID out of range.");
            return;
        }

        m_signatures[a_id] = a_signature;
    }
}