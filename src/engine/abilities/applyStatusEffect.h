#pragma once

#include "abilityEffect.h"
#include "../../entities/battleUnit.h"

#include <string>

class ApplyStatusEffect : public AbilityEffect {
public:
    ApplyStatusEffect(std::string effectName, int duration);

    void execute(BattleUnit* attacker, BattleUnit* defender);
private:
    std::string effectName;
    int duration;
};