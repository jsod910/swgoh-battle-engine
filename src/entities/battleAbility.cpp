#include "battleAbility.h"
#include "../engine/abilities/abilityDefinition.h"
#include "../engine/abilities/effects/effectContext.h"
#include "enums/abilitySlot.h"

#include <algorithm>
#include <iostream>

BattleAbility::BattleAbility(const AbilityDefinition* cachedRecipe, int baseCooldown, int initCooldown)
    : abilityRecipe(cachedRecipe), maxCooldown(baseCooldown), currentCooldown(initCooldown)
{
}

std::string BattleAbility::getName() const {
    return abilityRecipe->getName();
}
AbilitySlot BattleAbility::getSlot() const {
    return abilityRecipe->getSlot();
}
bool BattleAbility::isReady() const {
    // std::cout << getName() << " is ready to use: " << (currentCooldown == 0) << std::endl;
    return currentCooldown == 0;
}
int BattleAbility::getCurrentCooldown() const {
    return currentCooldown; 
}

void BattleAbility::decrementCooldown(int amount) {
    if(getSlot() == AbilitySlot::BASIC) return;

    // std::cout << "Current Cooldown: " << currentCooldown << " decreased by: " << amount << std::endl;
    currentCooldown = std::max(currentCooldown - amount, 0);
    // std::cout << "Current Cooldown is now: " << currentCooldown  << " for: " << getName() << std::endl;
}
void BattleAbility::resetCooldown() {
    currentCooldown = 0;
}
void BattleAbility::execute(EffectContext& context) {
    currentCooldown = maxCooldown;
    abilityRecipe->cast(context);
}
