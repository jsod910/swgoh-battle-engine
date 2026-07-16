#pragma once

#include <string>
#include <cstdint>

enum class ModifierType : uint8_t { FLAT = 0, PERCENT = 1 };
enum class ModifierStat : uint8_t {
    #define X(name) name,

    #include "modifierStat.def"

    #undef X

        COUNT
};

ModifierStat modifierStatFromString(const std::string& str);
const std::string modifierStatToString(ModifierStat stat);