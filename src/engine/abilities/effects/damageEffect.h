#pragma once

#include "abilityEffect.h"
#include "effectTypes.h"
#include "../../../entities/battleUnit.h"
#include "damageTypes.h"
#include "effectContext.h"

#include <string>

class DamageEffect : public AbilityEffect {
public:
    DamageEffect(const Effects::DamageEffectData& data);

    void execute(EffectContext& context);
    
    int calculateDamage(BattleUnit* attacker, BattleUnit* target, EffectContext& c);
    int getRegularDamage(BattleUnit* attacker, BattleUnit* target, double resolvedMulti);
    int getHealthPercentDamage(BattleUnit* target, double resolvedMulti);
    // int getMassiveDamage(BattleUnit* attacker, BattleUnit* target);

    bool isEvaded(BattleUnit* attacker, BattleUnit* target);
    bool isCrit(BattleUnit* attacker, BattleUnit* target);
private:
    DamageType damageType;
    ModifierStat offenseStat;
    ModifierStat defenseStat;
    
    Effects::Data::DynamicValue multiplier;

    bool canEvade;
    bool canCrit;
    bool ignoreDefense;

    inline bool isPhysical() const { return defenseStat == ModifierStat::FLAT_ARMOR; }
    
};
