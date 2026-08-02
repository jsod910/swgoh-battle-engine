#pragma once

#include "effectTypes.h"
#include "effectContext.h"

class BattleUnit;

#include <string>
#include <cstdint>

class RecoverEffect : public AbilityEffect {
public:
    RecoverEffect(const Effects::RecoverEffectData& d);

    void execute(EffectContext& c);

    int calculateRecover(BattleUnit* attacker, BattleUnit* target, EffectContext& c);
private:
    Effects::Data::DynamicValue value;
    Effects::Data::DynamicValue chance;
    ModifierType modType;

    ModifierStat stat;
    bool equalize;
};