#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <string>

#include "loaders/characterLoader.h"
#include "loaders/characterCache.h"
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

    CharacterCache cache;

    std::vector<std::string> masterCharacterList = {
        "luke",
        "vader"
    };

    cache.loadAllCharacters(masterCharacterList);
    std::cout << "Character Cache Loaded" << std::endl;
    std::cout << "====================================================" << std::endl;

    // const CharacterDefinition* player1 = cache.getCharacter("luke");
    // const CharacterDefinition* enemy1 = cache.getCharacter("vader");

    std::unique_ptr<BattleUnit> luke = std::make_unique<BattleUnit>(cache, "luke", Team::PLAYER);
    std::unique_ptr<BattleUnit> vader = std::make_unique<BattleUnit>(cache, "vader", Team::ENEMY);

    std::vector<std::unique_ptr<BattleUnit>> playerInputs;
    std::vector<std::unique_ptr<BattleUnit>> enemyInputs;

    playerInputs.push_back(std::move(luke));
    enemyInputs.push_back(std::move(vader));

    Battle battle(std::move(playerInputs), std::move(enemyInputs));
    battle.startBattle();

    std::cout << "Game Over" << std::endl;

    return 0;
}