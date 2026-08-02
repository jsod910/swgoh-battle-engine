#pragma once

#include <string>
#include <cstdint>

enum class ResolverType : uint8_t {
    #define X(name) name,

    #include "resolverType.def"

    #undef X

        COUNT
};

ResolverType resolverTypeFromString(const std::string& str);
const std::string resolverTypeToString(ResolverType r);