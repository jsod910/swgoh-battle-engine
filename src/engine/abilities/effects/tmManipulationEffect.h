#pragma once

#include "effectTypes.h"
#include "effectContext.h"

class BattleUnit;

class TMManipulationEffect : public AbilityEffect {
public:
    TMManipulationEffect(const Effects::TMManipulationData& d);

    void execute(EffectContext& c);
private:
    double chance;
    double value;

    bool checkResist(BattleUnit* attacker, BattleUnit* target) const;
};