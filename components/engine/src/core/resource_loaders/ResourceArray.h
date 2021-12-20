//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_RESOURCEARRAY_H
#define MAIN_RESOURCEARRAY_H

#include <unordered_map>
#include <cstdint>

#include "Logger.h"

namespace vis
{
    template<class T>
    class ResourceArray
    {
    public:
        ResourceArray(const ResourceArray& other) = delete;
        ResourceArray& operator=(const ResourceArray& other) = delete;

        ResourceArray()
        {
            m_index_to_resource = {};
            m_next_id = 0;
        }

        ~ResourceArray()
        {
            for(auto it = m_index_to_resource.begin(); it != m_index_to_resource.end(); it++)
            {
                T* resource = it->second;
                delete resource;
            }
        }

        std::uint16_t add_resource(T* a_resource)
        {
            m_index_to_resource.insert({m_next_id, a_resource});
            return m_next_id++;
        }

        T* get_resource(std::uint16_t a_id)
        {
            if(m_index_to_resource.find(a_id) == m_index_to_resource.end())
            {
                LOG_ERROR("Trying to return non existing mesh.");
                return nullptr;
            }

            return m_index_to_resource.at(a_id);
        }

        void delete_resource(std::uint16_t a_id)
        {
            if(m_index_to_resource.find(a_id) == m_index_to_resource.end())
            {
                LOG_WARNING("Trying to delete non existing resource");
                return;
            }

            T* resource = m_index_to_resource.at(a_id);
            m_index_to_resource.erase(a_id);

            delete resource;
        }
    private:
        std::unordered_map<std::uint16_t, T*> m_index_to_resource;
        std::uint16_t m_next_id;
    };
}

#endif //MAIN_RESOURCEARRAY_H
