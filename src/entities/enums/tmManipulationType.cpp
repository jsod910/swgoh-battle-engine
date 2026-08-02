#include "tmManipulationType.h"

#include <string>
#include <stdexcept>

TMManipulationType tmManipulationTypeFromString(const std::string& str){
#define X(name) \
    if(str == #name) return TMManipulationType::name;
    
#include "tmManipulationType.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string tmManipulationTypeToString(TMManipulationType r){
    switch(r){
#define X(name) \
        case TMManipulationType::name: return #name;

#include "tmManipulationType.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
