#include "battle.h"
#include "turnManager.h"
#include "targetingSystem.h"
#include "abilities/abilityEffect.h"

#include <iostream>

Battle::Battle(std::vector<std::unique_ptr<BattleUnit>> player, std::vector<std::unique_ptr<BattleUnit>> enemy)
    : playerList(std::move(player)), enemyList(std::move(enemy))
{
}

void Battle::startBattle(){
    std::cout << "starting battle" << std::endl;
    while(!isBattleOver()){
        // std::cout << "beginning next turn. Battle is over? " << isBattleOver() << std::endl;
        advanceNextTurn();
        // std::cout << "turn complete. battle is over? " << isBattleOver() << std::endl;
    }
}


std::vector<BattleUnit*> Battle::getPlayerUnits(){
    std::vector<BattleUnit*> rawPlayers;
    for(const auto& unitPtr : playerList)   rawPlayers.push_back(unitPtr.get());
    return rawPlayers;
}
std::vector<BattleUnit*> Battle::getEnemyUnits(){
    std::vector<BattleUnit*> rawEnemies;
    for(const auto& unitPtr : playerList)   rawEnemies.push_back(unitPtr.get());
    return rawEnemies;
}
std::vector<BattleUnit*> Battle::getAllUnits(){
    std::vector<BattleUnit*> rawAllUnits;

    for(const auto& unitPtr : playerList)   rawAllUnits.push_back(unitPtr.get());
    for(const auto& unitPtr : enemyList)   rawAllUnits.push_back(unitPtr.get());
    
    return rawAllUnits; 
}

double Battle::getCurrentBattleTime() const {
    return currentBattleTime;
}
void Battle::advanceBattleTime(double amount){
    currentBattleTime += amount;
}

// void Battle::performAttack(BattleUnit& attacker, BattleUnit& defender){
//     // std::cout << attacker.character->name << " is performing attack on " << defender.character->name << std::endl;
//     int damage = attacker.enterBattleStats.offense;

//     int newHealth = defender.currentViability.health - damage;

//     defender.currentViability.health = (newHealth > 0) ? newHealth : 0;

//     std::cout
//         << attacker.character->name
//         << " attacks "
//         << defender.character->name
//         << " for "
//         << damage
//         << " damage.\n";

//     std::cout
//         << defender.character->name
//         << " Current HP: "
//         << defender.currentViability.health;
        
//     if(!defender.isAlive()){
//         std::cout
//             << defender.character->name
//             << " was defeated.";
//     }    
        
//     std::cout    
//         << "\n\n";
// }

void Battle::advanceNextTurn(){
    TurnManager::turnResult turnRes = TurnManager::findTimeToNextTurn(getAllUnits());

    advanceBattleTime(turnRes.elapsedTime);

    for(auto& unit : playerList){
        // std::cout << unit->character->name << std::endl;
        if(unit->isAlive()){
            double tmGain = unit->getEffectiveStat(ModifierStat::SPEED) * turnRes.elapsedTime;
            unit->advanceTurnMeter(tmGain);
        }
    }
    for(auto& unit : enemyList){
        if(unit->isAlive()){
            double tmGain = unit->getEffectiveStat(ModifierStat::SPEED) * turnRes.elapsedTime;
            unit->advanceTurnMeter(tmGain);
        }
    }

    // std::cout << "found next turn" << std::endl;
    BattleUnit* actingUnit = turnRes.nextUnit;
    actingUnit->takeTurn();

    // std::cout << "next unit is: " << actingUnit.character->name << std::endl;
    // performAttack(actingUnit, *TargetingSystem::getSingleEnemyTarget(&actingUnit, *this));
    BattleUnit* target = TargetingSystem::getSingleEnemyTarget(actingUnit, this->getAllUnits());
    size_t abilityIdx = actingUnit->chooseBestAbility();
    actingUnit->executeAbility(abilityIdx, target, this->getAllUnits());
}

bool Battle::isBattleOver() const {
    bool playerAlive = false;
    bool enemyAlive = false;
    for(auto& unit : playerList){
        if(unit->isAlive()){
            playerAlive = true;
        }
    }
    for(auto& unit : enemyList){
        if(unit->isAlive()){
            enemyAlive = true;
        }
    }

    return !playerAlive || !enemyAlive;
}