#include "abilityEffectType.h"

#include <string>
#include <stdexcept>

AbilityEffectType abilityEffectTypeFromString(const std::string& str){
#define X(name) \
    if(str == #name) return AbilityEffectType::name;
    
#include "abilityEffectType.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string abilityEffectTypeToString(AbilityEffectType type){
    switch(type){
#define X(name) \
        case AbilityEffectType::name: return #name;

#include "abilityEffectType.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
