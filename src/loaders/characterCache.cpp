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

#include "../engine/abilities/effects/effectTypes.h"
#include "../engine/abilities/effects/damageEffect.h"
#include "../engine/abilities/effects/applyStatusEffect.h"
#include "../engine/abilities/effects/recoverEffect.h"
#include "../engine/abilities/effects/TMManipulationEffect.h"
#include "../engine/abilities/effects/modifyCooldownEffect.h"
#include "../engine/abilities/effects/TMSwapEffect.h"

#include "../entities/battleAbility.h"
#include "../entities/stats.h"
#include "../utils/enumUtils.h"
#include "../entities/enums/abilityEffectType.h"
#include "statusEffectCache.h"


using json = nlohmann::json;

void CharacterCache::loadCharacter(const std::string& filePath){
    if(statusEffectCache == nullptr){
        std::cerr << "[ERROR] Status Cache must be loaded before the Character Cache" << std::endl;
        return;
    }

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
        AbilitySlot slot = abilitySlotFromString(abilityData["slot"].get<std::string>());
        // std::cout << "Ability Slot: " << abilitySlotToString(slot) << std::endl;
        // std::string targetType = abilityData["targetType"];
        int baseCooldown = abilityData["baseCooldown"];
        int initCooldown = abilityData["initCooldown"];

        auto runtimeAbility = std::make_unique<AbilityDefinition>(aName, baseCooldown, initCooldown, slot);

        for(const auto& effect : abilityData["effects"]){
            AbilityEffectType effectType = abilityEffectTypeFromString(effect.at("type").get<std::string>());
            // Effects::AbilityEffectType effectType = parseEnum(effect.at("type").get<std::string>(), Effects::stringToAbilityEffectTypeMap);
            // std::cout << "reading ability effects: " << effectType << std::endl; 

            switch (effectType){
                case AbilityEffectType::DAMAGE:
                {
                    auto effectData = effect.get<Effects::DamageEffectData>();
                    runtimeAbility->effects.push_back(std::make_unique<DamageEffect>(effectData));
                    break;
                }
                case AbilityEffectType::APPLY_STATUS:
                {
                    auto effectData = effect.get<Effects::ApplyStatusEffectData>();
                    runtimeAbility->effects.push_back(std::make_unique<ApplyStatusEffect>(effectData, statusEffectCache->getStatusDefinition(effectData.name)));
                    break;
                }
                case AbilityEffectType::RECOVER:
                {
                    auto effectData = effect.get<Effects::RecoverEffectData>();
                    runtimeAbility->effects.push_back(std::make_unique<RecoverEffect>(effectData));
                    break;
                }
                case AbilityEffectType::MODIFY_TM:
                {
                    auto effectData = effect.get<Effects::TMManipulationData>();
                    runtimeAbility->effects.push_back(std::make_unique<TMManipulationEffect>(effectData));
                    break;
                }
                case AbilityEffectType::MODIFY_COOLDOWN:
                {
                    auto effectData = effect.get<Effects::ModifyCooldownEffectData>();
                    runtimeAbility->effects.push_back(std::make_unique<ModifyCooldownEffect>(effectData));
                    break;
                }
                case AbilityEffectType::SWAP_TM:
                {
                    auto effectData = effect.get<Effects::TMSwapEffectData>();
                    runtimeAbility->effects.push_back(std::make_unique<TMSwapEffect>(effectData));
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

const AbilityDefinition* CharacterCache::getAbility(const std::string& abilityID){
    if(abilityRegistry.find(abilityID) == abilityRegistry.end()){
        // std::cerr << "[ERROR] Ability Recipe not found: " << abilityID << std::endl;
        return nullptr;
    }

    return abilityRegistry[abilityID].get();    
}

void CharacterCache::loadAllCharacters(const std::vector<std::string>& allCharacterID){
    std::cout << "Boot Loading Characters into Cache..." << std::endl;
    
    if(statusEffectCache == nullptr){
        std::cerr << "[ERROR] Status Cache must be loaded before the Character Cache" << std::endl;
        return;
    }

    for(const std::string& characterID : allCharacterID){
        const CharacterDefinition* loaded = getCharacter(characterID);
        if(!loaded){
            std::cout << "[CRITICAL] Failed to cache: " << characterID << std::endl; 
        }
    }

    // std::cout << "Cache Initialization Complete. Total Loaded: " << characterRegistry.size() << std::endl;
}

void CharacterCache::setstatusEffectCache(const StatusEffectCache* cache){
    statusEffectCache = cache;
}