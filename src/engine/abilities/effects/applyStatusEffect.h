#pragma once

#include "abilityEffect.h"
#include "effectTypes.h"
#include "../../../entities/statusEffect.h"
#include "effectContext.h"
#include "../../events/eventTypes.h"

class BattleUnit;

#include <string>

class ApplyStatusEffect : public AbilityEffect {
public:
    ApplyStatusEffect(const Effects::ApplyStatusEffectData& data);

    void execute(EffectContext& c);

    bool applyStatus(BattleUnit* attacker, BattleUnit* target, StatusCategory category, ApplyStatusEvent& event);
private:
    StatusEffectType type;

    int duration;
    bool canDispel;
    bool canResist;
    bool canEvade;

    bool checkResist(BattleUnit* attacker, BattleUnit* target);
};