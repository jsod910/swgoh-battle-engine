#include "targetType.h"

#include <string>
#include <stdexcept>

TargetType targetTypeFromString(const std::string& str){
#define X(name) \
    if(str == #name) return TargetType::name;
    
#include "targetType.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string targetTypeToString(TargetType type){
    switch(type){
#define X(name) \
        case TargetType::name: return #name;

#include "targetType.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
