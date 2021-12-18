//
// Created by BlackFlage on 17.12.2021.
//

#include "Entity.h"

#define DEFAULT_NAME "default"

namespace vis
{
    int Entity::m_next_entity_suffix = 0;

    Entity::Entity(std::uint16_t a_id)
    {
        m_id = a_id;
        m_name = DEFAULT_NAME + std::to_string(m_next_entity_suffix++);
        m_type = EntityType::UNINITIALIZED;
    }

    Entity::Entity(std::uint64_t a_id, const std::string &a_name, EntityType a_type)
    {
        m_id = a_id;
        m_name = a_name;
        m_type = a_type;
    }

    void Entity::set_type(EntityType a_type)
    {
        m_type = a_type;
    }

    std::uint64_t Entity::get_id() const
    {
        return m_id;
    }

    std::string Entity::get_name() const
    {
        return m_name;
    }

    EntityType Entity::get_type() const
    {
        return m_type;
    }
}

