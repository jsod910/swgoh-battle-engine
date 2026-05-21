#include "battleAbility.h"
#include "../engine/abilities/ability.h"

BattleAbility::BattleAbility(const Ability* cachedRecipe, int baseCooldown, int initCooldown)
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
void BattleAbility::execute(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits) {
    abilityRecipe->cast(attacker, target, allUnits);
    currentCooldown = maxCooldown;
}
