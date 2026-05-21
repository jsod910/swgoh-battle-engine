#include "ability.h"
#include "../../entities/battleUnit.h"

#include <string>
#include <iostream>
#include <memory>

Ability::Ability(std::string name, int baseCooldown, int initCooldown) 
    : name(name), baseCooldown(baseCooldown), initCooldown(initCooldown)
{
}

void Ability::cast(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits) const {
    std::cout << attacker->getName() << " used " << this->name << " on " << target->getName() << std::endl;
    for(auto& effect : effects){
        effect->execute(attacker, target, allUnits);
    }
}

std::string Ability::getName() const {
    return name;
}
int Ability::getBaseCooldown() const {
    return baseCooldown;
}
int Ability::getInitCooldown() const {
    return initCooldown;
}