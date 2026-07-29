#pragma once

#include <string>
#include <cstdint>

enum class AbilitySlot : uint8_t {
    #define X(name) name,

    #include "abilitySlot.def"

    #undef X

        COUNT
};

AbilitySlot abilitySlotFromString(const std::string& str);
const std::string abilitySlotToString(AbilitySlot slot);