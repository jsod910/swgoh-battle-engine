#include "applyStatusEffect.h"
#include "../../../entities/enums/statusEffectType.h"
#include "../../../entities/statusEffect.h"
#include "../../rng.h"
#include "../../events/eventTypes.h"

#include <iostream>
#include <algorithm>

ApplyStatusEffect::ApplyStatusEffect(const Effects::ApplyStatusEffectData& d) 
    : AbilityEffect(d.targetType), type(d.statusEffectType), 
    duration(d.duration), canDispel(d.canDispel), canResist(d.canResist), canEvade(d.canEvade)
{
}

void ApplyStatusEffect::execute(EffectContext& c){
    std::cout << c.attacker->getName() << " is applying status: " << statusToString(type) << " to " << c.target->getName() << std::endl;

    // bool applied = false;

    ApplyStatusEvent event;
    event.attacker = c.attacker;
    event.target = c.target;
    event.statusType = type;
    event.statusCategory = getStatusCategory(type);

    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SINGLE_ENEMY:
        {
            applyStatus(c.attacker, c.target, event.statusCategory, event);
            break;
        }
        case TargetType::SELF:
        {
            applyStatus(c.attacker, c.attacker, event.statusCategory, event);
            break;
        }

        default:
            break;
    }
}

bool ApplyStatusEffect::applyStatus(BattleUnit* attacker, BattleUnit* target, StatusCategory category, ApplyStatusEvent& event){
    if(checkResist(attacker, target)){
        std::cout << "\nEFFECT RESISTED" << std::endl;    
        return false;
    }

    
    StatusEffectParams params;
    switch(category){
        case StatusCategory::BUFF:
        {
            params.type = type;
            params.category = category;
            params.stat = ModifierStat::PHYS_OFFENSE;
            params.modType = ModifierType::PERCENT;
            params.modValue = 0.5;
            params.duration = duration;
            params.dispellable = canDispel;
            params.sourceUnit = attacker;
            params.maxStacks = 1;
            break;
        }
        case StatusCategory::DEBUFF:
        {
            params.type = type;
            params.category = category;
            params.stat = ModifierStat::PHYS_OFFENSE;
            params.modType = ModifierType::PERCENT;
            params.modValue = -0.5;
            params.duration = duration;
            params.dispellable = canDispel;
            params.sourceUnit = attacker;
            params.maxStacks = 1;
            break;
        }

        default:
            return false;
    }

    target->applyStatus(StatusEffect(params));
    return true;
}

bool ApplyStatusEffect::checkResist(BattleUnit* attacker, BattleUnit* target){
    double potency = attacker->getEffectiveStat(ModifierStat::POTENCY);
    double tenacity = target->getEffectiveStat(ModifierStat::TENACITY);

    double chance = std::max(0.15, tenacity-potency);
    return BattleRNG::roll() <= chance;
}