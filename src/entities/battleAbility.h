#pragma once

#include "../engine/abilities/ability.h"

class BattleUnit;
class Ability;

class BattleAbility {
public:
    BattleAbility(const Ability* cachedRecipe, int baseCooldown, int initCooldown);

    std::string getName() const;
    bool isReady() const;
    int getCurrentCooldown() const;

    void decrementCooldown();
    void execute(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits);
private:
    const Ability* abilityRecipe;
    int maxCooldown;
    int currentCooldown;
};