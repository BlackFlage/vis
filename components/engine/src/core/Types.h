//
// Created by BlackFlage on 20.12.2021.
//

#ifndef MAIN_TYPES_H
#define MAIN_TYPES_H

#include <bitset>
#include <cstdint>

using Component = std::uint8_t;
using ComponentType = std::uint8_t;

#define MAX_ENTITIES 2048
#define MAX_COMPONENTS 128
#define MAX_RESOURCES 1000

using Signature = std::bitset<MAX_COMPONENTS>;

#endif //MAIN_TYPES_H
