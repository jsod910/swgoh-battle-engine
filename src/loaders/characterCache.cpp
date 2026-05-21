#include <unordered_map>
#include <string>
#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include "characterCache.h"
#include "../../external/json/json_loader.hpp"
#include "../entities/battleAbility.h"
#include "../engine/abilities/damageEffect.h"
#include "../entities/stats.h"
#include "../engine/abilities/effectTypes.h"
#include "../utils/enumUtils.h"
using json = nlohmann::json;

void CharacterCache::loadCharacter(const std::string& filePath){
    // std::cout << "Opening JSON: " << filePath << std::endl;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open file: " << filePath << std::endl;
        return;
    }
    json data = json::parse(file);
    file.close();
    // std::cout << "Closing JSON" << std::endl;

    std::unique_ptr<CharacterDefinition> character = std::make_unique<CharacterDefinition>();
    std::string characterID = data["id"];
    
    // std::cout << "read in some data" << std::endl;

    character->id = data["id"];
    character->name = data["name"];

    character->baseStats = data.at("stats").get<statData::Stats>();

    // character->baseStats.health = data["stats"]["health"];
    // character->baseStats.offense = data["stats"]["offense"];
    // character->baseStats.speed = data["stats"]["speed"];

    for(const auto& abilityData : data["abilities"]){
        // std::cout << "reading ability: " << abilityData["id"] << std::endl;
        character->abilityIds.push_back(abilityData["id"]);

        std::string aID = abilityData["id"];
        std::string aName = abilityData["name"];
        // std::string targetType = abilityData["targetType"];
        int baseCooldown = abilityData["baseCooldown"];
        int initCooldown = abilityData["initCooldown"];

        auto runtimeAbility = std::make_unique<Ability>(aName, baseCooldown, initCooldown);

        for(const auto& effect : abilityData["effects"]){
            Effects::AbilityEffectType effectType = parseEnum(effect.at("type").get<std::string>(), Effects::stringToAbilityEffectTypeMap);
            // std::cout << "reading ability effects: " << effectType << std::endl; 

            switch (effectType){
                case Effects::AbilityEffectType::DAMAGE:
                {
                    auto data = effect.get<Effects::DamageEffectData>();
                    runtimeAbility->effects.push_back(std::make_unique<DamageEffect>(data));
                    break;
                }
                default: break;
            }
        }
        abilityRegistry[aID] = std::move(runtimeAbility);
    }
    // std::cout << "all abilities loaded" << std::endl;
    characterRegistry[characterID] = std::move(character);

    // std::cout << "[SUCCESS] Boot-cached character and abilities for: " << characterID << std::endl;
}

const CharacterDefinition* CharacterCache::getCharacter(const std::string& characterID){
    if(characterRegistry.find(characterID) != characterRegistry.end()){
        return characterRegistry[characterID].get();    
    }

    std::string path = "../data/" + characterID + ".json";
    if(!std::filesystem::exists(path)){
        std::cerr << "[ERROR] Character file not found: " << path << std::endl;
        return nullptr;
    }

    // auto data = std::make_unique<CharacterDefinition>(CharacterLoader::loadCharacter(path));
    // characterRegistry[characterID] = std::move(data);
    // std::cout << "loading character: " << characterID << std::endl;
    loadCharacter(path);

    return characterRegistry[characterID].get();
}

const Ability* CharacterCache::getAbility(const std::string& abilityID){
    if(abilityRegistry.find(abilityID) == abilityRegistry.end()){
        // std::cerr << "[ERROR] Ability Recipe not found: " << abilityID << std::endl;
        return nullptr;
    }

    return abilityRegistry[abilityID].get();    
}

void CharacterCache::loadAllCharacters(const std::vector<std::string>& allCharacterID){
    std::cout << "Boot Loading Characters into Cache..." << std::endl;
    
    for(const std::string& characterID : allCharacterID){
        const CharacterDefinition* loaded = getCharacter(characterID);
        if(!loaded){
            std::cout << "[CRITICAL] Failed to cache: " << characterID << std::endl; 
        }
    }

    // std::cout << "Cache Initialization Complete. Total Loaded: " << characterRegistry.size() << std::endl;
}