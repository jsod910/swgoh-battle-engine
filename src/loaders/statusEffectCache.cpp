#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "statusEffectCache.h"
#include "../entities/enums/statusEffectType.h"
#include "../entities/statusEffectDefinition.h"

void StatusEffectCache::loadAllStatus(const std::string& filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open file: " << filePath << std::endl;
        return;
    }
    json data = json::parse(file);
    file.close();

    if (!data.is_array()) {
        std::cerr << "[ERROR] Status definitions must be a JSON array.\n";
        return;
    }

    for(const auto& effect : data){
        auto p = effect.get<StatusData::StatusDefinitionParams>();
        auto status = std::make_unique<StatusEffectDefinition>(p);

        size_t idx = static_cast<size_t>(p.name);
        
        if(statusEffectRegistry[idx]){
            std::cerr   << "[WARNING] Duplicate Status Definitions: "
                        << statusToString(p.name)
                        << std::endl;
        }

        std::cout << "Loaded at IDX: " << idx << std::endl;
        statusEffectRegistry[idx] = std::move(status);
    }
}

const StatusEffectDefinition* StatusEffectCache::getStatusDefinition(StatusEffectType name) const {
    std::cout << "Retrieving Status: " << statusToString(name) << " from idx: " << static_cast<size_t>(name) << std::endl;
    return statusEffectRegistry[static_cast<size_t>(name)].get();
}