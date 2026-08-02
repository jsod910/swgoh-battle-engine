#pragma once

#include <string>
#include <cstdint>

enum class TMManipulationType : uint8_t {
    #define X(name) name,

    #include "tmManipulationType.def"

    #undef X

        COUNT
};

TMManipulationType tmManipulationTypeFromString(const std::string& str);
const std::string tmManipulationTypeToString(TMManipulationType t);