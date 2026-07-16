#pragma once

#include <string>
#include <cstdint>

enum class TargetType : uint8_t {
    #define X(name) name,

    #include "targetType.def"

    #undef X
};

TargetType targetTypeFromString(const std::string& str);
const std::string targetTypeToString(TargetType type);
