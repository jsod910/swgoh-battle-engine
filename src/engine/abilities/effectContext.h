#pragma once

#include "../../entities/battleUnit.h"

class BattleUnit;
class Battle;

struct EffectContext {
    BattleUnit* attacker;
    BattleUnit* target;

    Battle* battle;
};

// struct DamageContext : EffectContext {

// };