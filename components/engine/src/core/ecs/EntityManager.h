//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_ENTITYMANAGER_H
#define MAIN_ENTITYMANAGER_H

#include <queue>
#include <array>
#include <unordered_map>

#include "Types.h"
#include "Entity.h"

namespace vis
{
    class EntityManager
    {
    public:
        void init();

        std::uint16_t create_entity();
        Entity get_entity(std::uint16_t a_id);
        void on_entity_destroyed(std::uint16_t a_id);

        Signature get_signature(std::uint16_t a_id);
        void set_signature(std::uint16_t a_id, Signature& a_signature);
    private:
        std::queue<std::uint16_t> m_available_entities;
        std::array<Signature, MAX_ENTITIES> m_signatures;
        std::unordered_map<std::uint16_t, Entity> m_entities;

        std::uint16_t m_living_entities;
    };
}

#endif //MAIN_ENTITYMANAGER_H
