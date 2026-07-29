#include "cooldownMode.h"

#include <string>
#include <stdexcept>

CooldownMode cooldownModeFromString(const std::string& str){
#define X(name) \
    if(str == #name) return CooldownMode::name;
    
#include "cooldownMode.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string cooldownModeToString(CooldownMode mode){
    switch(mode){
#define X(name) \
        case CooldownMode::name: return #name;

#include "cooldownMode.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
