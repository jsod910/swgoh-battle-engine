#pragma once

#include "effectTypes.h"
#include "effectContext.h"

class BattleUnit;

#include <string>
#include <cstdint>

class ModifyCooldownEffect : public AbilityEffect {
public:
    ModifyCooldownEffect(const Effects::ModifyCooldownEffectData& d);

    void execute(EffectContext& c);

    void triggerCooldown(BattleUnit* attacker, BattleUnit* target, EffectContext& c);
private:
    Effects::Data::DynamicValue amount;
    Effects::Data::DynamicValue chance;
    
    AbilitySlot slotTarget;
    CooldownMode mode;

    int getDelta(int amount) const;   // retrieves value needed with battleunit interface
};