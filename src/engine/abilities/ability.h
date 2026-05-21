#pragma once

#include <vector>
#include <string>

#include "../../entities/battleUnit.h"
#include "abilityEffect.h"

class AbilityEffect;
class BattleUnit;

class Ability {
public:
    std::vector<std::unique_ptr<AbilityEffect>> effects;

    Ability(std::string name, int baseCooldown, int initCooldown);

    void cast(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits) const;

    std::string getName() const;
    int getBaseCooldown() const;
    int getInitCooldown() const;
private:
    std::string name;
    int baseCooldown;
    int initCooldown;
    // std::string targetType;
};