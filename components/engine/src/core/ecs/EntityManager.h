//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_ENTITYMANAGER_H
#define MAIN_ENTITYMANAGER_H

#include <queue>
#include <array>

#include "Types.h"

namespace vis
{
    class EntityManager
    {
    public:
        void init();

        Entity create_entity();
        void on_entity_destroyed(const Entity& a_entity);

        Signature get_signature(const Entity& a_entity);
        void set_signature(const Entity& a_entity, const Signature& a_signature);
    private:
        std::queue<Entity> m_available_entities;
        std::array<Signature, MAX_ENTITIES> m_signatures;

        std::uint16_t m_living_entities;
    };
}

#endif //MAIN_ENTITYMANAGER_H
