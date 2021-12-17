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
        Scene(const std::string& a_name, std::set<Entity> a_entities);

        void add_entity(const Entity& a_entity);
        void remove_entity(const Entity& a_entity);
        void add_default_entity();

        std::set<Entity>& get_entities();
        const std::string& get_name() const;
    private:
        std::string m_name;
        std::set<Entity> m_entities;

        static int m_next_id;
    };
}

#endif //MAIN_SCENE_H
