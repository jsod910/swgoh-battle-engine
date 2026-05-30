#include "damageEffect.h"
#include "../../entities/battleUnit.h"
#include "../rng.h"
#include "../events/eventTypes.h"
#include "../battle.h"

#include <iostream>
#include <algorithm>
#include <cmath>

DamageEffect::DamageEffect(const Effects::DamageEffectData& data)
        : AbilityEffect(data.targetType), damageType(data.damageType),
        offenseStat(data.offense), defenseStat(data.defense),
        multiplier(data.multiplier), canEvade(data.canEvade), canCrit(data.canCrit),
        ignoreDefense(data.ignoreDefense)
{    
}

void DamageEffect::execute(EffectContext& context){
    // std::cout << attacker->getName() << " is performing attack on " << defender.character->name << std::endl;
    BattleUnit* attacker = context.attacker;
    BattleUnit* target = context.target;
    Battle* battle = context.battle;

    DamageEvent event;
    event.type = CombatEventType::DAMAGE_TAKEN;
    event.attacker = attacker;
    event.target = target;

    if(getTargetType() == TargetType::SINGLE_ENEMY){
        int damage = calculateDamage(attacker, target);
        target->takeDamage(damage);
        event.damage = damage;

        std::cout
            << attacker->getName()
            << " attacks "
            << target->getName()
            << " for "
            << damage
            << " damage.\n";
        std::cout
            << target->getName()
            << " Prot: "
            << target->getCurrentProtection()
            << " HP: "
            << target->getCurrentHealth();
        if(!target->isAlive()){
            std::cout
                << "\n"
                << target->getName()
                << " was defeated.";
        }

        battle->publishEvent(event);

    } else if(getTargetType() == TargetType::AOE_ENEMY){
        Team enemyTeam = target->getTeamID();

        for(BattleUnit* unit : battle->getAllUnits()){
            if(unit->getTeamID() == enemyTeam && unit->isAlive()){
                int damage = calculateDamage(attacker, unit);
                unit->takeDamage(damage);
                event.damage = damage;

                std::cout
                    << attacker->getName()
                    << " attacks "
                    << target->getName()
                    << " for "
                    << damage
                    << " damage.\n";
                std::cout
                    << unit->getName()
                    << " Prot: "
                    << unit->getCurrentProtection()
                    << " HP: "
                    << unit->getCurrentHealth();
                if(!unit->isAlive()){
                    std::cout
                        << "\n"
                        << unit->getName()
                        << " was defeated.";
                }
                battle->publishEvent(event);
            }
        }
    }    
        
    std::cout    
        << "\n\n";
}

int DamageEffect::calculateDamage(BattleUnit* attacker, BattleUnit* target) {
    if(isEvaded(attacker, target)){
        return 0;
    }
    switch(damageType) {
        case DamageType::REGULAR:
        case DamageType::TRUE:
            return getRegularDamage(attacker, target);
        case DamageType::PERCENT_HEALTH: 
            return getHealthPercentDamage(target);
        case DamageType::MASSIVE:
            return 99999; 
    }
    return 0;
}

int DamageEffect::getRegularDamage(BattleUnit* attacker, BattleUnit* target) {
    double critMultiplier = 1.0;
    if(isCrit(attacker, target) && damageType != DamageType::TRUE){
        critMultiplier = attacker->getEffectiveStat(ModifierStat::CRIT_DAMAGE);
    }
    
    int rawOffense = static_cast<int>(attacker->getEffectiveStat(offenseStat));
    if(ignoreDefense || damageType == DamageType::TRUE) {
        return rawOffense*multiplier*critMultiplier;
    }
    int rawDefense = static_cast<int>(target->getEffectiveStat(defenseStat));
    int defensePen = (defenseStat == ModifierStat::FLAT_ARMOR) ? 
        static_cast<int>(attacker->getEffectiveStat(ModifierStat::ARMOR_PEN)) :
        static_cast<int>(attacker->getEffectiveStat(ModifierStat::RESISTANCE_PEN));

    int effectiveDefense = std::max(0, rawDefense - defensePen);
    double dmgMitigation = effectiveDefense / (effectiveDefense + (85.0*7.5) );

    int finalDmg = (rawOffense*multiplier*critMultiplier) * (1-dmgMitigation);
    return finalDmg;
}
int DamageEffect::getHealthPercentDamage(BattleUnit* target) {
    int targetMaxHealth = target->getEffectiveStat(ModifierStat::HEALTH);
    int finalDmg = static_cast<int>(targetMaxHealth * multiplier);
    return finalDmg;
}
// int DamageEffect::getMassiveDamage(BattleUnit* attacker, BattleUnit* target) {
//     return 99999;
// }

bool DamageEffect::isEvaded(BattleUnit* attacker, BattleUnit* target) {
    if(!canEvade) return false;
    
    double evasion = isPhysical() ?
        target->getEffectiveStat(ModifierStat::DODGE) :
        target->getEffectiveStat(ModifierStat::DEFLECTION);
    double accuracy = isPhysical() ?
        attacker->getEffectiveStat(ModifierStat::PHYS_ACCURACY) :
        attacker->getEffectiveStat(ModifierStat::SPEC_ACCURACY);
        double evasionChance = std::max(0.0, evasion - accuracy);
    if(BattleRNG::roll() <= evasionChance){
        std::cout << "Attack was evaded" << std::endl;
        return true;
    }
    return false;
}
bool DamageEffect::isCrit(BattleUnit* attacker, BattleUnit* target) {
    if(!canCrit) return false;

    double critChance = isPhysical() ?
        attacker->getEffectiveStat(ModifierStat::PHYS_CRIT_CHANCE) :
        attacker->getEffectiveStat(ModifierStat::SPEC_CRIT_CHANCE);
    double critAvoid = target->getEffectiveStat(ModifierStat::CRIT_AVOIDANCE);
        double effectiveCritChance = std::max(0.0, critChance-critAvoid);
    if(BattleRNG::roll() <= effectiveCritChance){
        std::cout << "Critical Hit!" << std::endl;
        return true;
    }
    return false;
}