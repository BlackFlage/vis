//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <set>

#include "Types.h"

namespace vis
{
    class System
    {
    public:
        std::set<Entity> m_entities;
    };
}

#endif //MAIN_SYSTEM_H
