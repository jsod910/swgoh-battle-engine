#include "battle.h"
#include "turnManager.h"
#include "targetingSystem.h"
#include "abilities/effects/abilityEffect.h"
#include "events/eventManager.h"

#include <iostream>

Battle::Battle(std::vector<std::unique_ptr<BattleUnit>> player, std::vector<std::unique_ptr<BattleUnit>> enemy)
    : playerList(std::move(player)), enemyList(std::move(enemy))
{
    eventManager.subscribe(&debugListener);
}

void Battle::startBattle(){
    std::cout << "====================Battle Start====================\n" << std::endl;
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
void Battle::publishEvent(CombatEvent& event) const {
    eventManager.publish(event);
}
void Battle::addEventListener(EventListener* listener) {
    eventManager.subscribe(listener);
}

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

    // performAttack(actingUnit, *TargetingSystem::getSingleEnemyTarget(&actingUnit, *this));
    // BattleUnit* target = TargetingSystem::getSingleEnemyTarget(actingUnit, this->getAllUnits());
    size_t abilityIdx = actingUnit->chooseBestAbility();

    EffectContext context;
    context.attacker = actingUnit;
    context.target = TargetingSystem::getSingleEnemyTarget(actingUnit, this->getAllUnits());
    context.battle = this;
    actingUnit->executeAbility(abilityIdx, context);

    std::cout << "----------------------------------------------------\n" << std::endl;
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