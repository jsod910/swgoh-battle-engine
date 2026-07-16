#include "modifierStat.h"

#include <string>
#include <stdexcept>

ModifierStat modifierStatFromString(const std::string& str){
#define X(name) \
    if(str == #name) return ModifierStat::name;
    
#include "modifierStat.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string modifierStatToString(ModifierStat stat){
    switch(stat){
#define X(name) \
        case ModifierStat::name: return #name;

#include "modifierStat.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
