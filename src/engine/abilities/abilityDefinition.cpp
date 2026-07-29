#include "abilityDefinition.h"
#include "../../entities/battleUnit.h"
#include "effects/effectContext.h"

#include <string>
#include <iostream>
#include <memory>

AbilityDefinition::AbilityDefinition(std::string name, int baseCooldown, int initCooldown, AbilitySlot slot) 
    : name(name),
    baseCooldown(baseCooldown), initCooldown(initCooldown),
    slot(slot)
{
}

void AbilityDefinition::cast(EffectContext& context) const {
    std::cout << context.attacker->getName() << " used " << this->name << " on " << context.target->getName() << std::endl;
    for(auto& effect : effects){
        effect->execute(context);
    }
}

std::string AbilityDefinition::getName() const {
    return name;
}
int AbilityDefinition::getBaseCooldown() const {
    return baseCooldown;
}
int AbilityDefinition::getInitCooldown() const {
    return initCooldown;
}
AbilitySlot AbilityDefinition::getSlot() const {
    return slot;
}