#pragma once

#include "../../entities/battleUnit.h"
// #include "../../entities/enums/statusEffectType.h"

#include <cstdint>

class BattleUnit;
enum class StatusEffectType : uint8_t;
enum class StatusCategory;

enum class CombatEventType {
    DAMAGE_EVENT,
    STATUS_EVENT,
    TURN_START,
    TURN_END,
    ABILITY_USED,
    UNIT_DEFEATED
};

struct CombatEvent {
    CombatEventType type;

    CombatEvent(CombatEventType t) : type(t) {}
};
struct DamageEvent : CombatEvent {
    BattleUnit* attacker;
    BattleUnit* target;
    
    int damage;
    bool crit = false;
    bool canCounter = true;

    DamageEvent() : CombatEvent(CombatEventType::DAMAGE_EVENT) {}
};
struct ApplyStatusEvent : CombatEvent {
    BattleUnit* attacker;
    BattleUnit* target;

    StatusEffectType statusType;
    StatusCategory statusCategory;
    bool applied;

    ApplyStatusEvent() : CombatEvent(CombatEventType::STATUS_EVENT) {}
};