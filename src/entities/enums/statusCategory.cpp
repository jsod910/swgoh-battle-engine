#include "statusCategory.h"

#include <string>
#include <stdexcept>

StatusCategory statusCategoryFromString(const std::string& str){
#define X(name) \
    if(str == #name) return StatusCategory::name;
    
#include "statusCategory.def"

#undef X

    throw std::runtime_error("Unknown status: " + str);
}

const std::string statusCategoryToString(StatusCategory category){
    switch(category){
#define X(name) \
        case StatusCategory::name: return #name;

#include "statusCategory.def"

#undef X

        default:
            return "UNKNOWN";
    }
}
