#pragma once

#include "../engine/abilities/abilityDefinition.h"
#include "../engine/abilities/effects/effectContext.h"
#include "enums/abilitySlot.h"


class BattleUnit;
class AbilityDefinition;

class BattleAbility {
public:
    BattleAbility(const AbilityDefinition* cachedRecipe, int baseCooldown, int initCooldown);

    std::string getName() const;
    AbilitySlot getSlot() const;
    bool isReady() const;
    int getCurrentCooldown() const;

    void decrementCooldown(int amount);
    void resetCooldown();
    void execute(EffectContext& context);
private:
    const AbilityDefinition* abilityRecipe;
    int maxCooldown;
    int currentCooldown;
};