#pragma once

#include "abilityEffect.h"
#include "effectTypes.h"
#include "../../entities/battleUnit.h"
#include "damageTypes.h"

#include <string>


class DamageEffect : public AbilityEffect {
public:
    DamageEffect(const Effects::DamageEffectData& data);

    void execute(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits);
    
    int calculateDamage(BattleUnit* attacker, BattleUnit* target);
    int getRegularDamage(BattleUnit* attacker, BattleUnit* target);
    int getHealthPercentDamage(BattleUnit* target);
    // int getMassiveDamage(BattleUnit* attacker, BattleUnit* target);

    bool isEvaded(BattleUnit* attacker, BattleUnit* target);
    bool isCrit(BattleUnit* attacker, BattleUnit* target);
private:
    DamageType damageType;
    ModifierStat offenseStat;
    ModifierStat defenseStat;
    
    double multiplier;

    bool canEvade;
    bool canCrit;
    bool ignoreDefense;

    inline bool isPhysical() const { return defenseStat == ModifierStat::FLAT_ARMOR; }
    
};
