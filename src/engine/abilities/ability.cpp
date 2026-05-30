#include "ability.h"
#include "../../entities/battleUnit.h"
#include "effectContext.h"

#include <string>
#include <iostream>
#include <memory>

ActiveAbility::ActiveAbility(std::string name, int baseCooldown, int initCooldown) 
    : name(name), baseCooldown(baseCooldown), initCooldown(initCooldown)
{
}

void ActiveAbility::cast(EffectContext& context) const {
    // std::cout << context.attacker->getName() << " used " << this->name << " on " << context.target->getName() << std::endl;
    for(auto& effect : effects){
        effect->execute(context);
    }
}

std::string ActiveAbility::getName() const {
    return name;
}
int ActiveAbility::getBaseCooldown() const {
    return baseCooldown;
}
int ActiveAbility::getInitCooldown() const {
    return initCooldown;
}