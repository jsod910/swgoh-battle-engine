#pragma once

#include <string>
#include <cstdint>

enum class AbilityEffectType : uint8_t {
    #define X(name) name,

    #include "abilityEffectType.def"

    #undef X
};

AbilityEffectType abilityEffectTypeFromString(const std::string& str);
const std::string abilityEffectTypeToString(AbilityEffectType type);
