#include "modifyCooldownEffect.h"
#include "effectTypes.h"
#include "../../../entities/battleUnit.h"
#include "../../battle.h"

#include <iostream>

ModifyCooldownEffect::ModifyCooldownEffect(const Effects::ModifyCooldownEffectData& d)
    : AbilityEffect(d.targetType),
    chance(d.chance), slotTarget(d.slot), mode(d.mode)
{
    if(mode == CooldownMode::INCREASE) amount = -d.amount;
    else amount = d.amount;
}

void ModifyCooldownEffect::execute(EffectContext& c){
    std::cout << "Modifying Cooldowns. ";

    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SELF:
        {
            // std::cout << "reducing cooldowns on self ";
            triggerCooldown(c.attacker, c.attacker);
            break;
        }
        case TargetType::SINGLE_ALLY:
        {
            triggerCooldown(c.attacker, c.target);
            break;
        }
        case TargetType::SINGLE_ENEMY:
        {
            triggerCooldown(c.attacker, c.target);
            break;
        }
        case TargetType::AOE_ALLY:
        {
            const auto& unitList = c.battle->getTeamUnits(c.attacker->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                triggerCooldown(c.attacker, unit.get());
            }
            break;
        }
        case TargetType::AOE_ENEMY:
        {
            const auto& unitList = c.battle->getTeamUnits(c.target->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                triggerCooldown(c.attacker, unit.get());
            }
            break;
        }

        default: ;
    }

    std::cout << "Done Modifying Cooldowns." << std::endl;
}

void ModifyCooldownEffect::triggerCooldown(BattleUnit* attacker, BattleUnit* target){
    // std::cout << "triggering cooldowns with slot: " << abilitySlotToString(slotTarget) << " and mode: " << cooldownModeToString(mode) << std::endl;
    switch(slotTarget){
        case AbilitySlot::ALL:
        {
            // std::cout << "resetting all cooldowns ";
            if(mode == CooldownMode::RESET) target->resetAllAbilityCooldowns();
            else target->decrementAllAbilityCooldowns(amount);
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