#include "applyStatusEffect.h"
#include "../../../entities/enums/statusEffectType.h"
#include "../../../entities/statusEffect.h"
#include "../../rng.h"
#include "../../events/eventTypes.h"
#include "../resolver.h"

#include <iostream>
#include <algorithm>

ApplyStatusEffect::ApplyStatusEffect(const Effects::ApplyStatusEffectData& d, const StatusEffectDefinition* definition) 
    : AbilityEffect(d.targetType), statusDefinition(definition),
    chance(d.chance), stacks(d.stacks), duration(d.duration),
    canDispel(d.canDispel), canResist(d.canResist), canEvade(d.canEvade)
{
    // std::cout << "Constructor Status Definition: " << definition << std::endl;
}

void ApplyStatusEffect::execute(EffectContext& c){
    // std::cout << "Status Definition is: " << statusDefinition << std::endl;
    std::cout << c.attacker->getName() << " is applying status: " << statusToString(statusDefinition->getName()) << " to " << c.target->getName() << std::endl;

    TargetType targetType = getTargetType();
    int resolvedStacks = Resolver::resolveDynamicValue(stacks, c);
    switch(targetType){
        case TargetType::SINGLE_ENEMY:
        {
            for(auto i = 0; i < resolvedStacks; ++i){
                applyStatus(c.attacker, c.target, c);
            }
            break;
        }
        case TargetType::SELF:
        {
            for(auto i = 0; i < resolvedStacks; ++i){
                applyStatus(c.attacker, c.target, c);
            }
            break;
        }

        default:
            break;
    }
}

bool ApplyStatusEffect::applyStatus(BattleUnit* attacker, BattleUnit* target, EffectContext& c){
    if(checkResist(attacker, target)){
        std::cout << "\nEFFECT RESISTED" << std::endl;    
        return false;
    }
    std::cout << "\nEFFECT APPLIED" << std::endl;

    
    StatusEffectParams p;
    p.def = statusDefinition;
    p.duration = static_cast<int>(Resolver::resolveDynamicValue(duration, c));
    p.dispellable = canDispel;
    p.sourceUnit = attacker;
    target->applyStatus(p);

    return true;
}

bool ApplyStatusEffect::checkResist(BattleUnit* attacker, BattleUnit* target) const {
    double potency = attacker->getEffectiveStat(ModifierStat::POTENCY);
    double tenacity = target->getEffectiveStat(ModifierStat::TENACITY);

    double odds = std::max(0.15, tenacity-potency);
    return BattleRNG::roll() <= odds;
}