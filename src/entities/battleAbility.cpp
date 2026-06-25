#include "battleAbility.h"
#include "../engine/abilities/ability.h"
#include "../engine/abilities/effects/effectContext.h"

#include <algorithm>

BattleAbility::BattleAbility(const ActiveAbility* cachedRecipe, int baseCooldown, int initCooldown)
    : abilityRecipe(cachedRecipe), maxCooldown(baseCooldown), currentCooldown(initCooldown)
{
}

std::string BattleAbility::getName() const {
    return abilityRecipe->getName();
}
bool BattleAbility::isReady() const {
    return currentCooldown == 0;
}
int BattleAbility::getCurrentCooldown() const {
    return currentCooldown; 
}

void BattleAbility::decrementCooldown(int amount) {
    if(currentCooldown > 0) currentCooldown = std::max(currentCooldown - amount, 0);
}
void BattleAbility::execute(EffectContext& context) {
    abilityRecipe->cast(context);
    currentCooldown = maxCooldown;
}
