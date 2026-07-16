#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <string>

#include "loaders/characterLoader.h"
#include "loaders/characterCache.h"
#include "loaders/statusEffectCache.h"
#include "entities/battleUnit.h"
#include "engine/battle.h"

int main() {
    // std::cout << "STARTING CharacterLoader Test" << std::endl;

    // CharacterDefinition player1 = CharacterLoader::loadCharacter("../data/luke.json");
    // CharacterDefinition enemy1 = CharacterLoader::loadCharacter("../data/vader.json");

    // std::cout << "====================================================" << std::endl;
    // std::cout << "CharacterLoader Test Results" << std::endl;
    // std::cout << "====================================================" << std::endl;

    // std::cout << "Player's Character: " << player1.name << std::endl;
    // std::cout << "Player's Health: " << player1.baseStats.health << std::endl;
    // std::cout << "Player's Offense: " << player1.baseStats.offense << std::endl;
    // std::cout << "Player's Basic Ability: " << player1.abilityIds[0].name << std::endl;

    
    // std::cout << "Enemy's Character: " << enemy1.name << std::endl;
    // std::cout << "Enemy's Health: " << enemy1.baseStats.health << std::endl;
    // std::cout << "Enemy's Offense: " << enemy1.baseStats.offense << std::endl;
    // std::cout << "Enemy's Basic Ability: " << enemy1.abilityIds[0].name << std::endl;

    StatusEffectCache statusCache;
    CharacterCache characterCache;

    statusCache.loadAllStatus("../data/statusEffects.json");
    characterCache.setstatusEffectCache(&statusCache);

    std::vector<std::string> masterCharacterList = {
        "luke",
        "vader"
    };

    characterCache.loadAllCharacters(masterCharacterList);
    std::cout << "Character Cache Loaded" << std::endl;
    std::cout << "====================================================" << std::endl;

    // const CharacterDefinition* player1 = cache.getCharacter("luke");
    // const CharacterDefinition* enemy1 = cache.getCharacter("vader");

    std::unique_ptr<BattleUnit> luke = std::make_unique<BattleUnit>(characterCache, "luke", Team::PLAYER);
    std::unique_ptr<BattleUnit> vader = std::make_unique<BattleUnit>(characterCache, "vader", Team::ENEMY);

    std::vector<std::unique_ptr<BattleUnit>> playerInputs;
    std::vector<std::unique_ptr<BattleUnit>> enemyInputs;

    playerInputs.push_back(std::move(luke));
    enemyInputs.push_back(std::move(vader));

    Battle battle(std::move(playerInputs), std::move(enemyInputs));
    battle.startBattle();

    std::cout << "Game Over" << std::endl;

    return 0;
}