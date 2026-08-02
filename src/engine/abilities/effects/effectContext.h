#pragma once

#include "../../../entities/battleUnit.h"

class BattleUnit;
class Battle;


struct EffectResults {
    int damageDealt = 0;
    int damageInstances = 0;

    int buffsAppliedCount = 0;
    int buffsDispelledCount = 0;
    int debuffsAppliedCount = 0;
    int debuffsDispelledCount = 0;

    double tmGained = 0.0;
    int tmGainedInstances = 0;

    int unitsDefeated = 0;
    int unitsRevived = 0;
};

struct EffectContext {
    BattleUnit* attacker;
    BattleUnit* target;

    Battle* battle;

    EffectResults rtValues;
};
