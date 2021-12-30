//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_MAINMANAGER_H
#define MAIN_MAINMANAGER_H

#include <memory>
#include <set>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"


namespace vis
{
    class MainManager
    {
    public:
        MainManager() = default;
        MainManager(const MainManager& a_other) = delete;
        MainManager& operator=(const MainManager a_other) = delete;

        static void init()
        {
            m_instance = std::make_shared<MainManager>();
            m_instance->create_managers();
        }

        std::uint16_t create_entity()
        {
            return m_entity_manager->create_entity();
        }

        void destroy_entity(std::uint16_t a_id)
        {
            m_entity_manager->on_entity_destroyed(a_id);
            m_component_manager->on_entity_destroyed(a_id);
            m_system_manager->on_entity_destroyed(a_id);

            if(m_current_entity == a_id)
            {
                m_current_entity = MAX_ENTITIES + 1;
            }
        }

        void set_current_entity(std::uint16_t a_id)
        {
            m_current_entity = a_id;
        }

        std::uint16_t get_current_entity() const
        {
            return m_current_entity;
        }

        Entity get_entity(std::uint16_t a_id)
        {
            return m_entity_manager->get_entity(a_id);
        }

        template<typename T>
        T& get_component(std::uint16_t a_id)
        {
            return m_component_manager->get_component<T>(a_id);
        }

        template<typename T>
        void add_component(std::uint16_t a_id, T a_component)
        {
            m_component_manager->add_component<T>(a_id, a_component);

            Signature signature = m_entity_manager->get_signature(a_id);
            signature.set(m_component_manager->get_component_type<T>(), true);

            m_entity_manager->set_signature(a_id, signature);
            m_system_manager->on_entity_signature_changed(a_id, signature);
        }

        template<typename T>
        void register_component()
        {
            m_component_manager->register_component<T>();
        }

        template<typename T>
        std::shared_ptr<T> register_system()
        {
            return m_system_manager->register_system<T>();
        }

        template<typename T>
        ComponentType get_component_type()
        {
            return m_component_manager->get_component_type<T>();
        }

        template<typename T>
        void set_system_signature(const Signature& a_signature)
        {
            m_system_manager->set_signature<T>(a_signature);
        }

        static std::shared_ptr<MainManager> get_instance()
        {
            return m_instance;
        }

        Signature get_entity_signature(std::uint16_t a_id)
        {
            return m_entity_manager->get_signature(a_id);
        }
    private:
        void create_managers()
        {
            m_entity_manager = std::make_unique<EntityManager>();
            m_entity_manager->init();

            m_component_manager = std::make_unique<ComponentManager>();
            m_component_manager->init();

            m_system_manager = std::make_unique<SystemManager>();
            m_system_manager->init();

            m_current_entity = MAX_ENTITIES;
        }
    private:
        std::unique_ptr<EntityManager>      m_entity_manager;
        std::unique_ptr<ComponentManager>   m_component_manager;
        std::unique_ptr<SystemManager>      m_system_manager;
        static std::shared_ptr<MainManager> m_instance;

        std::uint16_t                       m_current_entity;
    };
}

#endif //MAIN_MAINMANAGER_H
