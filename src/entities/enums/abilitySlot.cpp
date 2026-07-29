#include "abilitySlot.h"

#include <string>
#include <stdexcept>

AbilitySlot abilitySlotFromString(const std::string& str){
#define X(name) \
    if(str == #name) return AbilitySlot::name;
    
#include "abilitySlot.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string abilitySlotToString(AbilitySlot slot){
    switch(slot){
#define X(name) \
        case AbilitySlot::name: return #name;

#include "abilitySlot.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
