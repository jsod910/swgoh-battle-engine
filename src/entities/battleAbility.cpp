#include "battleAbility.h"
#include "../engine/abilities/ability.h"
#include "../engine/abilities/effectContext.h"

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

void BattleAbility::decrementCooldown() {
    if(currentCooldown > 0) currentCooldown--;
}
void BattleAbility::execute(EffectContext& context) {
    abilityRecipe->cast(context);
    currentCooldown = maxCooldown;
}
