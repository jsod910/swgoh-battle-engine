#include "modifyCooldownEffect.h"
#include "effectTypes.h"
#include "../../../entities/battleUnit.h"
#include "../../battle.h"
#include "../resolver.h"

#include <iostream>

ModifyCooldownEffect::ModifyCooldownEffect(const Effects::ModifyCooldownEffectData& d)
    : AbilityEffect(d.targetType),
    amount(d.amount), chance(d.chance),
    slotTarget(d.slot), mode(d.mode)    
{}

void ModifyCooldownEffect::execute(EffectContext& c){
    std::cout << "Modifying Cooldowns. ";

    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SELF:
        {
            // std::cout << "reducing cooldowns on self ";
            triggerCooldown(c.attacker, c.attacker, c);
            break;
        }
        case TargetType::SINGLE_ALLY:
        {
            triggerCooldown(c.attacker, c.target, c);
            break;
        }
        case TargetType::SINGLE_ENEMY:
        {
            triggerCooldown(c.attacker, c.target, c);
            break;
        }
        case TargetType::AOE_ALLY:
        {
            const auto& unitList = c.battle->getTeamUnits(c.attacker->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                triggerCooldown(c.attacker, unit.get(), c);
            }
            break;
        }
        case TargetType::AOE_ENEMY:
        {
            const auto& unitList = c.battle->getTeamUnits(c.target->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                triggerCooldown(c.attacker, unit.get(), c);
            }
            break;
        }

        default: ;
    }

    std::cout << "Done Modifying Cooldowns." << std::endl;
}

void ModifyCooldownEffect::triggerCooldown(BattleUnit* attacker, BattleUnit* target, EffectContext& c){
    // std::cout << "triggering cooldowns with slot: " << abilitySlotToString(slotTarget) << " and mode: " << cooldownModeToString(mode) << std::endl;
    int resolvedAmount = getDelta( static_cast<int>(Resolver::resolveDynamicValue(amount, c)) );
    
    switch(slotTarget){
        case AbilitySlot::ALL:
        {
            // std::cout << "resetting all cooldowns ";
            if(mode == CooldownMode::RESET) target->resetAllAbilityCooldowns();
            else target->decrementAllAbilityCooldowns(resolvedAmount);
            // std::cout << "done resetting cooldowns." << std::endl;
            break;
        }
        
        default:
        {
            // if(mode == CooldownMode::RESET) target->resetAbilityCooldown(slotTarget);
            // target->decrementAbilityCooldown(slotTarget, amount);
        }
    }
}

int ModifyCooldownEffect::getDelta(int val) const {
    if(mode == CooldownMode::INCREASE) return -val;
    else return val;
}