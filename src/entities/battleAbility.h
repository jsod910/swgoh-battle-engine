#pragma once

#include "../engine/abilities/ability.h"
#include "../engine/abilities/effectContext.h"

class BattleUnit;
class ActiveAbility;

class BattleAbility {
public:
    BattleAbility(const ActiveAbility* cachedRecipe, int baseCooldown, int initCooldown);

    std::string getName() const;
    bool isReady() const;
    int getCurrentCooldown() const;

    void decrementCooldown();
    void execute(EffectContext& context);
private:
    const ActiveAbility* abilityRecipe;
    int maxCooldown;
    int currentCooldown;
};