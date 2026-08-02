#include "resolverType.h"

#include <string>
#include <stdexcept>

ResolverType resolverTypeFromString(const std::string& str){
#define X(name) \
    if(str == #name) return ResolverType::name;
    
#include "resolverType.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string resolverTypeToString(ResolverType r){
    switch(r){
#define X(name) \
        case ResolverType::name: return #name;

#include "resolverType.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
