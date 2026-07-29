#pragma once

#include <string>
#include <cstdint>

enum class CooldownMode : uint8_t {
    #define X(name) name,

    #include "cooldownMode.def"

    #undef X

        COUNT
};

CooldownMode cooldownModeFromString(const std::string& str);
const std::string cooldownModeToString(CooldownMode mode);