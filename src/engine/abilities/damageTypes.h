#pragma once

#include <unordered_map>
#include <string>

enum class DamageType { REGULAR, TRUE, PERCENT_HEALTH, MASSIVE };
inline const std::unordered_map<std::string, DamageType> stringToDamageTypeMap =
    {  
        {"REGULAR", DamageType::REGULAR},
        {"TRUE", DamageType::TRUE},
        {"PERCENT_HEALTH", DamageType::PERCENT_HEALTH},
        {"MASSIVE", DamageType::MASSIVE}
    };