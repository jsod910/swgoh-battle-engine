#pragma once

#include "abilityEffect.h"
#include "../../entities/battleUnit.h"

class HealEffect : public AbilityEffect {
public:
    HealEffect(double mult);

    void execute(BattleUnit* healer, BattleUnit* healee);
private:
    double multiplier;
};