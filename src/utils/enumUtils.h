#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

template<typename EnumType>
EnumType parseEnum(
    const std::string& value,
    const std::unordered_map<std::string, EnumType>& enumMap
)
{
    auto it = enumMap.find(value);

    if(it == enumMap.end()){
        throw std::runtime_error("Invalid enum string: " + value);
    }

    return it->second;
}