#pragma once

#include "battle.h"
#include "../entities/battleUnit.h"

class TargetingSystem {
public:
    static BattleUnit* getSingleEnemyTarget(const BattleUnit* attacker, const std::vector<BattleUnit*>& allUnits);
};
