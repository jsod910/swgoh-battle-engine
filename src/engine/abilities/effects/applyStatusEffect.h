#pragma once

#include "abilityEffect.h"
#include "effectTypes.h"
#include "../../../entities/statusEffect.h"
#include "effectContext.h"
#include "../../events/eventTypes.h"

class BattleUnit;
class StatusEffectDefinition;

#include <string>

class ApplyStatusEffect : public AbilityEffect {
public:
    ApplyStatusEffect(const Effects::ApplyStatusEffectData& data, const StatusEffectDefinition* definition);

    void execute(EffectContext& c);

    bool applyStatus(BattleUnit* attacker, BattleUnit* target, EffectContext& c);
private:
    const StatusEffectDefinition* statusDefinition;

    Effects::Data::DynamicValue chance;
    Effects::Data::DynamicValue stacks;
    Effects::Data::DynamicValue duration;

    bool canDispel;
    bool canResist;
    bool canEvade;

    bool checkResist(BattleUnit* attacker, BattleUnit* target) const;
};