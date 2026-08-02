#pragma once

#include "effectTypes.h"
#include "effectContext.h"
#include "../../../entities/enums/tmManipulationType.h"

class BattleUnit;

class TMManipulationEffect : public AbilityEffect {
public:
    TMManipulationEffect(const Effects::TMManipulationData& d);

    void execute(EffectContext& c);
private:
    Effects::Data::DynamicValue value;
    Effects::Data::DynamicValue chance;

    TMManipulationType type;
    bool canResist;

    bool checkResist(BattleUnit* attacker, BattleUnit* target) const;
    double getDelta(double val) const;
};