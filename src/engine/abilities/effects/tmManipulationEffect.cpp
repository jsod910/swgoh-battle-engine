#include "tmManipulationEffect.h"
#include "effectTypes.h"
#include "../../../entities/battleUnit.h"
#include "../../battle.h"
#include "../../rng.h"

#include <iostream>

TMManipulationEffect::TMManipulationEffect(const Effects::TMManipulationData& d)
    : AbilityEffect(d.targetType),
    chance(d.chance), value(d.value)
{}

void TMManipulationEffect::execute(EffectContext& c){
    double delta = value * 1000;    // 1000 is value at 100% TM
    std::cout << "TM Manipulation of: " << delta << std::endl;

    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SELF:
        {
            c.attacker->modifyTurnMeter(delta);
            break;
        }
        case TargetType::SINGLE_ALLY:
        {
            c.target->modifyTurnMeter(delta);
            break;
        }
        case TargetType::SINGLE_ENEMY:
        {
            if(!checkResist(c.attacker, c.target)) c.target->modifyTurnMeter(delta);
            else std::cout << "TM Effect Resisted." << std::endl;
            break;
        }
        case TargetType::AOE_ALLY:
        {

            const auto& unitList = c.battle->getTeamUnits(c.attacker->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                unit->modifyTurnMeter(delta);
            }
            break;
        }
        case TargetType::AOE_ENEMY:
        {
            const auto& unitList = c.battle->getTeamUnits(c.target->getTeamID());
            for(const auto& unit : unitList){
                if(!unit->isAlive()) continue;
                if(!checkResist(c.attacker, unit.get())) unit->modifyTurnMeter(delta);
            }
            break;
        }
        default: ;
    }

    std::cout << "Finished TM Manipulation" << std::endl;
}

bool TMManipulationEffect::checkResist(BattleUnit* attacker, BattleUnit* target) const {
    double potency = attacker->getEffectiveStat(ModifierStat::POTENCY);
    double tenacity = target->getEffectiveStat(ModifierStat::TENACITY);

    double odds = std::max(0.15, tenacity-potency);
    return BattleRNG::roll() <= odds;
}