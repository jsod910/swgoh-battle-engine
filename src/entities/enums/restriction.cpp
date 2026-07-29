#include "restriction.h"

#include <string>
#include <stdexcept>

Restriction restrictionFromString(const std::string& str){
#define X(name) \
    if(str == #name) return Restriction::name;
    
#include "restriction.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string restrictionToString(Restriction r){
    switch(r){
#define X(name) \
        case Restriction::name: return #name;

#include "restriction.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
