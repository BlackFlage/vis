//
// Created by BlackFlage on 17.12.2021.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H

#include <string>

#include "Types.h"

namespace vis
{
    enum class EntityType
    {
        DEFAULT,
        CUBE,
        SPHERE,
        EMPTY,
        CUSTOM,
        UNINITIALIZED,
        BUFFER_FULL
    };

    class Entity
    {
    public:
        Entity(std::uint16_t a_id);
        Entity(std::uint64_t a_id, const std::string& a_name, EntityType a_type);
        void set_type(EntityType a_type);

        std::uint64_t get_id() const;
        std::string get_name() const;
        EntityType get_type() const;
    private:
        std::string m_name;
        std::uint64_t m_id;

        EntityType m_type;

        static int m_next_entity_suffix;
    };
}

#endif //MAIN_ENTITY_H
