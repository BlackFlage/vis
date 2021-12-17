//
// Created by BlackFlage on 17.12.2021.
//

#include "Scene.h"

#include <string>
#include <ecs/components/BasicComponents.h>
#include "ecs/MainManager.h"
#include "OBJLoader.h"

namespace vis
{
    int Scene::m_next_id = 0;

    Scene::Scene()
    {
        m_name = "default" + std::to_string(m_next_id++);
        m_entities = std::set<Entity>{};

        add_default_entity();
    }

    Scene::Scene(const std::string& a_name, std::set<Entity> a_entities)
    {
        m_name = a_name;
        m_entities = std::move(a_entities);
    }

    std::set<Entity>& Scene::get_entities()
    {
        return m_entities;
    }

    const std::string &Scene::get_name() const
    {
        return m_name;
    }

    void Scene::add_entity(const Entity &a_entity)
    {
        m_entities.insert(a_entity);
    }

    void Scene::remove_entity(const Entity &a_entity)
    {
        m_entities.erase(a_entity);
    }

    void Scene::add_default_entity()
    {
        Entity e = main_manager->create_entity();

        main_manager->add_component(e, Transform{
                .m_position = glm::vec3(0.0f, 0.0f, -10.0f),
                .m_rotation = glm::vec3(1.0f),
                .m_scale = glm::vec3(1.0f)
        });

        main_manager->add_component(e, Color{
            .m_color = glm::vec3(0.3f, 0.0f, 1.0f)
        });

        main_manager->add_component(e, OBJLoader::load_from_models("cube/cube.obj", "cube"));

        main_manager->set_current_entity(e);
        m_entities.insert(e);
    }
}