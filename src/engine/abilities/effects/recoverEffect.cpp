#include "recoverEffect.h"
#include "effectTypes.h"
#include "../../../entities/battleUnit.h"
#include "../../battle.h"
#include "../resolver.h"

#include <iostream>
#include <algorithm>
#include <vector>

RecoverEffect::RecoverEffect(const Effects::RecoverEffectData& d)
    : AbilityEffect(d.targetType),
    value(d.value), chance(d.chance),
    modType(d.modType), stat(d.stat), equalize(d.equalize)
{} 


void RecoverEffect::execute(EffectContext& c){
    std::cout << "Recovering Health or Protection" << std::endl;

    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SINGLE_ALLY:
        {
            c.target->recoverViability(stat, calculateRecover(c.attacker, c.target, c));
            break;
        }
        case TargetType::SELF:
        {
            c.attacker->recoverViability(stat, calculateRecover(c.attacker, c.attacker, c));
            break;
        }
        case TargetType::AOE_ALLY:
        {
            const auto& unitList = c.battle->getTeamUnits(c.attacker->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                unit->recoverViability(stat, calculateRecover(c.attacker, unit.get(), c));
            }
            break;
        }

        default:
            break;
    }

    std::cout << "Finished Recovery" << std::endl;
}

int RecoverEffect::calculateRecover(BattleUnit* attacker, BattleUnit* target, EffectContext& c){
    double resolvedValue = Resolver::resolveDynamicValue(value, c);

    if(modType == ModifierType::FLAT) return static_cast<int>(resolvedValue);
    return static_cast<int>( static_cast<int>(target->getEffectiveStat(stat)) * resolvedValue );
}