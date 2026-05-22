#include "battleUnit.h"
#include "../loaders/characterCache.h"
#include "statusEffect.h"
#include "stats.h"

#include <string>
#include <cmath>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>

BattleUnit::BattleUnit(CharacterCache& cache, const std::string& charID, Team team)
{
    character = cache.getCharacter(charID);
    teamID = team;

    enterBattleStats = character->baseStats;
    currentViability.health = enterBattleStats.health;
    currentViability.protection = enterBattleStats.protection;
    turnMeter = 0.0f;

    for(const std::string& abilityID : character->abilityIds){
        const Ability* recipe = cache.getAbility(abilityID);
        int baseCooldown = recipe->getBaseCooldown();
        int initCooldown = recipe->getInitCooldown();

        runtimeAbilities.push_back(BattleAbility(recipe, baseCooldown, initCooldown));
    }
}

std::string BattleUnit::getName() const {
    return character->name;
}
Team BattleUnit::getTeamID() const {
    return teamID;
}
double BattleUnit::getTurnMeter() const {
    return turnMeter;
}
bool BattleUnit::isAlive() const {
    return currentViability.health > 0;
}

void BattleUnit::advanceTurnMeter(double amount) {
    turnMeter += amount;
}
void BattleUnit::takeTurn() {
    turnMeter -= 1000.0;
    for(auto& ability : runtimeAbilities){
        ability.decrementCooldown();
    }
}
void BattleUnit::takeDamage(int amount) {
    if(currentViability.protection > 0 && amount > currentViability.protection){
        amount -= currentViability.protection;
        currentViability.protection = 0;
        currentViability.health = std::max(0, (currentViability.health-amount));
    } else if(currentViability.protection > 0){
        currentViability.protection -= amount;
    } else {
        currentViability.health = (amount > currentViability.health) ? 0 : (currentViability.health - amount);
    }
}
void recoverHealth(int amount);
void recoverProtection(int amount);
void BattleUnit::executeAbility(size_t idx, BattleUnit* target, const std::vector<BattleUnit*>& allUnits){
    if(idx > runtimeAbilities.size()) { 
        std::cout << "[ERROR] Ability does not exist" << std::endl;
        return; 
    }
    BattleAbility* ability = &runtimeAbilities[idx];
    ability->execute(this, target, allUnits);
}

size_t BattleUnit::chooseBestAbility() const {
    for(size_t i = runtimeAbilities.size(); i > 0; i--){
        size_t idx = i-1;
        if(runtimeAbilities[idx].isReady()) return idx;
    }

    return 0;
}

// stat retrieval getters
double BattleUnit::getEffectiveStat(ModifierStat type) const {
    double baseStat = enterBattleStats.getStatValue(type);
    double multiplier = 1.0;
    double flatAddition = 0.0;

    for(const auto& effect : activeEffects){
        if(effect.getStat() == type){
            if(effect.getModType() == ModifierType::PERCENT){
                multiplier += effect.getModValue();
            } else {
                flatAddition += effect.getModValue();
            }
        }
    }

    double effectiveStat = (baseStat * multiplier) + flatAddition;
    // if(statData::isFlatStat(type)) { return std::floor(effectiveStat); }
    return effectiveStat;
}
int BattleUnit::getCurrentHealth() const {
    return currentViability.health;
}
int BattleUnit::getCurrentProtection() const {
    return currentViability.protection;
}