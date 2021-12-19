//
// Created by BlackFlage on 16.12.2021.
//

#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <set>

#include "ecs/EntityManager.h"

namespace vis
{
    class Scene
    {
    public:
        Scene();
        Scene(const std::string& a_name);
        Scene(const std::string& a_name, std::set<std::uint16_t> a_entities);

        void add_entity(std::uint16_t a_id);
        void remove_entity(std::uint16_t a_id);

        void add_entity(EntityType a_type = EntityType::EMPTY);

        std::set<std::uint16_t>& get_entities();
        const std::string& get_name() const;
    private:
        std::string get_suffix_from_type(EntityType a_type);
    private:
        std::string m_name;
        std::set<std::uint16_t> m_entities;
    };
}

#endif //MAIN_SCENE_H
