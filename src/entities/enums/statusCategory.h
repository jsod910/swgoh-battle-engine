#pragma once

#include <string>
#include <cstdint>

enum class StatusCategory : uint8_t {
    #define X(name) name,

    #include "statusCategory.def"

    #undef X

        COUNT
};

StatusCategory statusCategoryFromString(const std::string& str);
const std::string statusCategoryToString(StatusCategory category);