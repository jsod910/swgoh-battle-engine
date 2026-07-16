#include "applyStatusEffect.h"
#include "../../../entities/enums/statusEffectType.h"
#include "../../../entities/statusEffect.h"
#include "../../rng.h"
#include "../../events/eventTypes.h"

#include <iostream>
#include <algorithm>

ApplyStatusEffect::ApplyStatusEffect(const Effects::ApplyStatusEffectData& d, const StatusEffectDefinition* definition) 
    : AbilityEffect(d.targetType), statusDefinition(definition),
    duration(d.duration), canDispel(d.canDispel), canResist(d.canResist), canEvade(d.canEvade)
{
    // std::cout << "Constructor Status Definition: " << definition << std::endl;
}

void ApplyStatusEffect::execute(EffectContext& c){
    // std::cout << "Status Definition is: " << statusDefinition << std::endl;
    std::cout << c.attacker->getName() << " is applying status: " << statusToString(statusDefinition->getName()) << " to " << c.target->getName() << std::endl;

    // bool applied = false;

    ApplyStatusEvent event;
    event.attacker = c.attacker;
    event.target = c.target;
    event.statusDefinition = statusDefinition;

    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SINGLE_ENEMY:
        {
            applyStatus(c.attacker, c.target, event);
            break;
        }
        case TargetType::SELF:
        {
            applyStatus(c.attacker, c.attacker, event);
            break;
        }

        default:
            break;
    }
}

bool ApplyStatusEffect::applyStatus(BattleUnit* attacker, BattleUnit* target, ApplyStatusEvent& event){
    if(checkResist(attacker, target)){
        std::cout << "\nEFFECT RESISTED" << std::endl;    
        return false;
    }
    std::cout << "\nEFFECT APPLIED" << std::endl;

    
    StatusEffectParams p;
    p.def = statusDefinition;
    p.duration = duration;
    p.dispellable = canDispel;
    p.sourceUnit = attacker;
    target->applyStatus(p);

    return true;
}

bool ApplyStatusEffect::checkResist(BattleUnit* attacker, BattleUnit* target){
    double potency = attacker->getEffectiveStat(ModifierStat::POTENCY);
    double tenacity = target->getEffectiveStat(ModifierStat::TENACITY);

    double chance = std::max(0.15, tenacity-potency);
    return BattleRNG::roll() <= chance;
}