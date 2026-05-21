#include "damageEffect.h"
#include "../../entities/battleUnit.h"
#include "../rng.h"

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

void DamageEffect::execute(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits){
    // std::cout << attacker->getName() << " is performing attack on " << defender.character->name << std::endl;
    
    if(getTargetType() == TargetType::SINGLE_ENEMY){
        int damage = calculateDamage(attacker, target);
        target->takeDamage(damage);

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

    } else if(getTargetType() == TargetType::AOE_ENEMY){
        Team enemyTeam = target->getTeamID();

        for(BattleUnit* unit : allUnits){
            if(unit->getTeamID() == enemyTeam && unit->isAlive()){
                int damage = calculateDamage(attacker, unit);
                unit->takeDamage(damage);

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

            }
        }
    }    
        
    std::cout    
        << "\n\n";
}

int DamageEffect::calculateDamage(BattleUnit* attacker, BattleUnit* target) {
    switch(damageType) {
        case DamageType::REGULAR: return getRegularDamage(attacker, target); 
        default: return 0;
    }
    return 0;
}

int DamageEffect::getRegularDamage(BattleUnit* attacker, BattleUnit* target) {
    if(isEvaded(attacker, target)){
        return 0;
    }
    if(isCrit(attacker, target)){
        multiplier *= attacker->getEffectiveStat(ModifierStat::CRIT_DAMAGE);
    }
    
    int rawOffense = static_cast<int>(attacker->getEffectiveStat(offenseStat));
    // std::cout << "ATTACK OFFENSE: " << rawOffense << std::endl;
    int rawDefense = static_cast<int>(target->getEffectiveStat(defenseStat));
    int defensePen = (defenseStat == ModifierStat::FLAT_ARMOR) ? 
        static_cast<int>(attacker->getEffectiveStat(ModifierStat::ARMOR_PEN)) :
        static_cast<int>(attacker->getEffectiveStat(ModifierStat::RESISTANCE_PEN));

    int effectiveDefense = std::max(0, rawDefense - defensePen);
    // std::cout << "TARGET DEFENSE: " << effectiveDefense << std::endl;
    double dmgMitigation = effectiveDefense / (effectiveDefense + (85.0*7.5) );
    // std::cout << "DAMAGE MITIGATION: " << dmgMitigation << std::endl;

    int finalDmg = (rawOffense*multiplier) * (1-dmgMitigation);
    return finalDmg;
}

bool DamageEffect::isEvaded(BattleUnit* attacker, BattleUnit* target) {
    double evasion = isPhysical() ?
        target->getEffectiveStat(ModifierStat::DODGE) :
        target->getEffectiveStat(ModifierStat::DEFLECTION);
    double accuracy = isPhysical() ?
        attacker->getEffectiveStat(ModifierStat::PHYS_ACCURACY) :
        attacker->getEffectiveStat(ModifierStat::SPEC_ACCURACY);
    if(canEvade) {
        double evasionChance = std::max(0.0, evasion - accuracy);
        if(BattleRNG::roll() <= evasionChance){
            std::cout << "Attack was evaded" << std::endl;
            return true;
        }
    }

    return false;
}
bool DamageEffect::isCrit(BattleUnit* attacker, BattleUnit* target) {
    double critChance = isPhysical() ?
        attacker->getEffectiveStat(ModifierStat::PHYS_CRIT_CHANCE) :
        attacker->getEffectiveStat(ModifierStat::SPEC_CRIT_CHANCE);
    double critAvoid = target->getEffectiveStat(ModifierStat::CRIT_AVOIDANCE);
    if(canCrit) {
        double effectiveCritChance = std::max(0.0, critChance-critAvoid);
        if(BattleRNG::roll() <= effectiveCritChance){
            std::cout << "Critical Hit!" << std::endl;
            return true;
        }
    }

    return false;
}