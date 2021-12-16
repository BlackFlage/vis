//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_COMPONENTMANAGER_H
#define MAIN_COMPONENTMANAGER_H

#include <unordered_map>
#include <memory>

#include "Types.h"
#include "ComponentArray.h"

namespace vis
{
    class ComponentManager
    {
    public:
        void init()
        {
            m_component_arrays = std::unordered_map<const char*, std::shared_ptr<IComponentArray>>();
            m_component_types = std::unordered_map<const char*, ComponentType>();
            m_next_component_type = 0;
        }

        void on_entity_destroyed(const Entity& a_entity)
        {
            for(auto& comp_pair : m_component_arrays)
            {
                auto& array = comp_pair.second;
                array->on_entity_destroyed(a_entity);
            }
        }

        template<typename T>
        void register_component()
        {
            const char* component_name = typeid(T).name();

            if(m_component_types.find(component_name) != m_component_types.end())
            {
                LOG_WARNING("Trying to register component: {0} more than once!", component_name);
                return;
            }

            m_component_arrays.insert({component_name, std::make_shared<ComponentArray<T>>()});
            m_component_types.insert({component_name, m_next_component_type});

            m_next_component_type++;
        }

        template<typename T>
        ComponentType get_component_type()
        {
            const char* component_name = typeid(T).name();

            if(m_component_types.find(component_name) == m_component_types.end())
            {
                LOG_WARNING("Component: {0} not registered before use!", component_name);
                return 0;
            }

            return m_component_types[component_name];
        }

        template<typename T>
        void add_component(const Entity& a_entity, T& a_component)
        {
            get_component_array<T>()->add_data(a_entity, a_component);
        }

        template<typename T>
        void remove_component(const Entity& a_entity)
        {
            get_component_array<T>()->remove_data(a_entity);
        }

        template<typename T>
        T& get_component(const Entity& a_entity)
        {
            return get_component_array<T>()->get_data(a_entity);
        }
    private:
        template<typename T>
        std::shared_ptr<ComponentArray<T>> get_component_array()
        {
            const char* component_name = typeid(T).name();

            if(m_component_arrays.find(component_name) == m_component_arrays.end())
            {
                LOG_WARNING("Failed to retrieve ComponentArray of type: {0}. Component maybe be not registered before use!", component_name);
                return nullptr;
            }

            return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[component_name]);
        }
    private:
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_component_arrays;
        std::unordered_map<const char*, ComponentType> m_component_types;
        ComponentType m_next_component_type;
    };
}

#endif //MAIN_COMPONENTMANAGER_H
