#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "characterLoader.h"
#include "../engine/abilities/ability.h"
#include "../entities/battleAbility.h"

class ActiveAbility;
class StatusEffectCache;

class CharacterCache {
public:
    void loadCharacter(const std::string& filePath);
    void loadAllCharacters(const std::vector<std::string>& allCharacterID);

    const CharacterDefinition* getCharacter(const std::string& characterID);
    const ActiveAbility* getAbility(const std::string& abilityID);

    void setstatusEffectCache(const StatusEffectCache* cache);

private:
    std::unordered_map<std::string, std::unique_ptr<CharacterDefinition>> characterRegistry;
    std::unordered_map<std::string, std::unique_ptr<ActiveAbility>> abilityRegistry;

    const StatusEffectCache* statusEffectCache;
};