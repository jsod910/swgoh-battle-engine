#include "tmSwapEffect.h"
#include "effectTypes.h"
#include "../../../entities/battleUnit.h"

#include <iostream>

TMSwapEffect::TMSwapEffect(const Effects::TMSwapEffectData& d)
    : AbilityEffect(d.targetType)
{}

void TMSwapEffect::execute(EffectContext& c){
    std::cout << "Swapping TM with: " << c.attacker->getName() << " and " << c.target->getName() << std::endl;

    double unitTM = c.attacker->getTurnMeter();
    TargetType targetType = getTargetType();
    switch(targetType){
        case TargetType::SINGLE_ALLY:
        {
            c.attacker->setTurnMeter(c.target->getTurnMeter());
            c.target->setTurnMeter(unitTM + 1000.0);
            break;
        }
        case TargetType::SINGLE_ENEMY:
        {
            c.attacker->setTurnMeter(c.target->getTurnMeter());
            c.target->setTurnMeter(unitTM + 1000.0);
            break;
        }

        default: ;
    }
}