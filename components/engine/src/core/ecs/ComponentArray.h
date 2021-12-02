//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_COMPONENTARRAY_H
#define MAIN_COMPONENTARRAY_H

#include "unordered_map"

#include "Types.h"
#include "Logger.h"

namespace vis
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void on_entity_destroyed(const Entity& a_entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        ComponentArray();

        void add_data(const Entity& a_entity, T& a_data);
        void remove_data(const Entity& a_entity);

        T& get_data(const Entity& a_entity);
        void on_entity_destroyed(const Entity& a_entity) override;
    private:
        std::array<T, MAX_ENTITIES> m_component_array;
        std::unordered_map<Entity, size_t> m_entity_to_index;
        std::unordered_map<size_t, Entity> m_index_to_entity;

        size_t m_current_size;
    };

    template<typename T>
    ComponentArray<T>::ComponentArray()
    {
        m_current_size = 0;
    }

    template<typename T>
    void ComponentArray<T>::add_data(const Entity &a_entity, T& a_data)
    {
        if(m_entity_to_index.find(a_entity) != m_entity_to_index.end())
        {
            LOG_WARNING("Trying to add data to entity: {0} more than once!", a_entity);
            return;
        }

        size_t data_index = m_current_size;
        m_component_array[data_index] = a_data;
        m_entity_to_index[a_entity] = data_index;
        m_index_to_entity[data_index] = a_entity;
        m_current_size++;
    }

    template<typename T>
    void ComponentArray<T>::remove_data(const Entity &a_entity)
    {
        if(m_entity_to_index.find(a_entity) == m_entity_to_index.end())
        {
            LOG_WARNING("Trying to remove non existing data from entity: {0}", a_entity);
            return;
        }

        size_t index_of_removed_entity = m_entity_to_index[a_entity];

        m_component_array[index_of_removed_entity] = m_component_array[m_current_size - 1];
        m_entity_to_index[m_current_size - 1] = index_of_removed_entity;
        m_index_to_entity[index_of_removed_entity] = m_current_size - 1;

        m_entity_to_index.erase(a_entity);
        m_index_to_entity.erase(m_current_size - 1);

        m_current_size--;
    }

    template<typename T>
    T& ComponentArray<T>::get_data(const Entity &a_entity)
    {
        if(m_entity_to_index.find(a_entity) == m_entity_to_index.end())
        {
            LOG_WARNING("Trying to pull non existing data from entity: {0}", a_entity);
            return T{};
        }

        return m_component_array[m_entity_to_index[a_entity]];
    }

    template<typename T>
    void ComponentArray<T>::on_entity_destroyed(const Entity &a_entity)
    {
        if(m_entity_to_index.find(a_entity) != m_entity_to_index.end())
        {
            remove_data(a_entity);
        }
    }
}

#endif //MAIN_COMPONENTARRAY_H