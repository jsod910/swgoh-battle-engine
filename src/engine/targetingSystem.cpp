#include "targetingSystem.h"
#include "battle.h"
#include "../entities/battleUnit.h"

#include <vector>

BattleUnit* TargetingSystem::getSingleEnemyTarget(const BattleUnit* attacker, const std::vector<BattleUnit*>& allUnits){
    for(BattleUnit* unit : allUnits){
        if(unit != attacker && unit->isAlive()){
            return unit;
        }
    }

    return nullptr;
}