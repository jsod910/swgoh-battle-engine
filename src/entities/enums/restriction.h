#pragma once

#include <string>
#include <cstdint>

enum class Restriction : uint8_t {
    #define X(name) name,

    #include "restriction.def"

    #undef X

        COUNT
};

Restriction restrictionFromString(const std::string& str);
const std::string restrictionToString(Restriction r);