//
// Created by BlackFlage on 02.12.2021.
//

#ifndef MAIN_TYPES_H
#define MAIN_TYPES_H

#include <bitset>
#include <cstdint>

using Entity = std::uint16_t;
using Component = std::uint8_t;
using ComponentType = std::uint8_t;

#define MAX_ENTITIES 1024
#define MAX_COMPONENTS 128

using Signature = std::bitset<MAX_COMPONENTS>;

#endif //MAIN_TYPES_H
