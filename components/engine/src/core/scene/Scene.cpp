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
    Scene::Scene()
    {

    }

    Scene::Scene(const std::string& a_name, std::set<std::uint16_t> a_entities)
    {
        m_name = a_name;
        m_entities = std::move(a_entities);
    }

    std::set<std::uint16_t>& Scene::get_entities()
    {
        return m_entities;
    }

    const std::string& Scene::get_name() const
    {
        return m_name;
    }

    void Scene::add_entity(std::uint16_t a_id)
    {
        m_entities.insert(a_id);
    }

    void Scene::remove_entity(std::uint16_t a_id)
    {
        m_entities.erase(a_id);
    }

    void Scene::add_entity(EntityType a_type)
    {
        std::uint16_t e = main_manager->create_entity();
        glm::vec3 scale = glm::vec3(1.0f);

        if(a_type == EntityType::SPHERE)
        {
            scale = glm::vec3(0.3f);
        }

        main_manager->set_current_entity(e);
        m_entities.insert(e);

        if(a_type == EntityType::EMPTY)
        {
            return;
        }

        main_manager->add_component(e, Transform{
                .m_position = glm::vec3(0.0f, 0.0f, -10.0f),
                .m_rotation = glm::vec3(1.0f),
                .m_scale = scale
        });

        std::string suffix = get_suffix_from_type(a_type);
        Mesh mesh = OBJLoader::load_from_models("default\\" + suffix + ".obj", suffix);

        main_manager->add_component(e, Color{
            .m_color = glm::vec3(0.3f, 0.3f, 0.3f)
        });

        main_manager->add_component(e, mesh);
    }

    std::string Scene::get_suffix_from_type(EntityType a_type)
    {
        switch(a_type)
        {
            case EntityType::CUBE:
                return "cube";
            case EntityType::SPHERE:
                return "sphere";
        }
        return "";
    }
}