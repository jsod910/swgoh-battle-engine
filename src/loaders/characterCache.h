#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "characterLoader.h"
#include "../engine/abilities/ability.h"
#include "../entities/battleAbility.h"

class Ability;

class CharacterCache {
public:
    void loadCharacter(const std::string& filePath);
    void loadAllCharacters(const std::vector<std::string>& allCharacterID);

    const CharacterDefinition* getCharacter(const std::string& characterID);
    const Ability* getAbility(const std::string& abilityID);

private:
    std::unordered_map<std::string, std::unique_ptr<CharacterDefinition>> characterRegistry;
    std::unordered_map<std::string, std::unique_ptr<Ability>> abilityRegistry;
};