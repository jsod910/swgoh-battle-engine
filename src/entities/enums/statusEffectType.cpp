#include "statusEffectType.h"
#include "../statusEffect.h"

#include <string>
#include <stdexcept>

StatusEffectType statusFromString(const std::string& str){
#define X(name) \
    if(str == #name) return StatusEffectType::name;
    
#include "statusEffectType.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string statusToString(StatusEffectType type){
    switch(type){
#define X(name) \
        case StatusEffectType::name: return #name;

#include "statusEffectType.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
