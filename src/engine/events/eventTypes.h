#pragma once

#include "../../entities/battleUnit.h"

class BattleUnit;

enum class CombatEventType {
    DAMAGE_TAKEN,
    TURN_START,
    TURN_END,
    ABILITY_USED,
    UNIT_DEFEATED
};

struct CombatEvent {
    CombatEventType type;
};
struct DamageEvent : CombatEvent {
    BattleUnit* attacker;
    BattleUnit* target;
    
    int damage;
    bool crit = false;
    bool canCounter = true;
};