#include "battleUnit.h"
#include "../loaders/characterCache.h"
#include "statusEffect.h"
#include "stats.h"
#include "../engine/abilities/effects/effectContext.h"

#include <string>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>

BattleUnit::BattleUnit(CharacterCache& cache, const std::string& charID, Team team)
{
    character = cache.getCharacter(charID);
    teamID = team;

    enterBattleStats = character->baseStats;
    currentViability.health = enterBattleStats.health;
    currentViability.protection = enterBattleStats.protection;
    turnMeter = 0.0f;

    for(const std::string& abilityID : character->abilityIds){
        const ActiveAbility* recipe = cache.getAbility(abilityID);
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
    // std::cout << "taking turn" << std::endl;
    
    turnMeter -= 1000.0;
    tickCooldowns();
}

void BattleUnit::tickCooldowns(){
    decrementAllAbilityCooldowns();
    decrementStatusDurations();
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
void BattleUnit::executeAbility(size_t idx, EffectContext& context){
    if(idx > runtimeAbilities.size()) { 
        std::cout << "[ERROR] Ability does not exist" << std::endl;
        return; 
    }
    BattleAbility* ability = &runtimeAbilities[idx];
    ability->execute(context);
}

size_t BattleUnit::chooseBestAbility() const {
    for(size_t i = runtimeAbilities.size(); i > 0; i--){
        size_t idx = i-1;
        if(runtimeAbilities[idx].isReady()) return idx;
    }

    return 0;
}

// STAT RETRIEVAL GETTERS
double BattleUnit::getEffectiveStat(ModifierStat stat) const {
    // std::cout << "GETTING STAT: " << static_cast<size_t>(stat) << std::endl;

    double baseStat = enterBattleStats.getStatValue(stat);
    double multiplier = 1.0 + getCachedModifier(stat, ModifierType::PERCENT);
    double flatAddition = getCachedModifier(stat, ModifierType::FLAT);

    // for(const auto& effect : activeEffects){
    //     if(effect.getStat() == stat){
    //         if(effect.getModType() == ModifierType::PERCENT){
    //             multiplier += effect.getModValue();
    //         } else {
    //             flatAddition += effect.getModValue();
    //         }
    //     }
    // }

    double effectiveStat = (baseStat * multiplier) + flatAddition;
    // std::cout << "STAT VALUE: " << effectiveStat << std::endl;
    return effectiveStat;
}
int BattleUnit::getCurrentHealth() const {
    return currentViability.health;
}
int BattleUnit::getCurrentProtection() const {
    return currentViability.protection;
}
void BattleUnit::updateCachedModifier(ModifierStat stat, ModifierType type, double val) {
    size_t idx = static_cast<size_t>(stat);

    if(type == ModifierType::PERCENT) cachedModifiers.percent[idx] += val;
    else cachedModifiers.flat[idx] += val;


}
double BattleUnit::getCachedModifier(ModifierStat stat, ModifierType type) const {
    size_t idx = static_cast<size_t>(stat);

    if(type == ModifierType::PERCENT) return cachedModifiers.percent[idx];
    else return cachedModifiers.flat[idx];
}


// STATUS EFFECT MAINTENENCE
bool BattleUnit::hasStatus(StatusEffectType type) const {
    return getEffectStacks(type) > 0;   // 0 - no stacks (false) >0 - has Stacks (true)
}
void BattleUnit::applyStatus(const StatusEffect& effect){
    StatusEffectType type = effect.getType();
    // only apply status if effect is NOT at maxStacks 
    if(getEffectStacks(type) < effect.getMaxStacks() || effect.getMaxStacks() == -1){
        // add effect to vector and update num of stacks
        activeEffects.push_back(effect);
        addEffectStacks(type);

        // update cached values
        updateCachedModifier(effect.getStat(), effect.getModType(), effect.getModValue());
    } else {    // else update the existing copy
        for(auto& existing : activeEffects){
            if(type == existing.getType()){
                existing.setDuration( std::max(existing.getDuration(), effect.getDuration()) );
                existing.setDispellable( existing.isDispellable() | effect.isDispellable() );
            }
        }
    }
}
int BattleUnit::removeAllStatus(StatusCategory type){
    int removedCount = 0;
    size_t i = 0;
    while(i < activeEffects.size()){
        StatusEffect& effect = activeEffects[i];
        if(effect.getCategory() == type && effect.isDispellable()){
            removeStatusAtIndex(i);
            removedCount++;
        } else {
            i++;    // only increment i when we do not remove an effect
        }
    }
    return removedCount;
}

int BattleUnit::getEffectStacks(StatusEffectType type) const {
    size_t index = static_cast<size_t>(type);
    if(effectStacks[index] != 255){
        return effectStacks[index];
    }
    auto it = overflowStacks.find(type);
    if(it != overflowStacks.end()){
        return it->second;
    }
    return effectStacks[index];
}
void BattleUnit::addEffectStacks(StatusEffectType type, int amount){
    size_t index = static_cast<size_t>(type);

    if(effectStacks[index] == 255){
        overflowStacks[type] += amount;
    } 
    else if(effectStacks[index]+amount >= 255){
        overflowStacks[type] = effectStacks[index] + amount;
        effectStacks[index] = 255;
    } else {
        effectStacks[index] += static_cast<uint8_t>(amount);
    }
}
void BattleUnit::removeStatusAtIndex(size_t index){
    if(index >= activeEffects.size()) return;  // check bounds
    
    StatusEffectType removedType = activeEffects[index].getType();
    size_t stacksIndex = static_cast<size_t>(removedType);
    

    // revert cached value
    double val = activeEffects[index].getModValue();
    updateCachedModifier(activeEffects[index].getStat(), activeEffects[index].getModType(), -val);
    // swap and pop from back
    activeEffects[index] = activeEffects.back();
    activeEffects.pop_back();
    // activeEffects.erase(activeEffects.begin() + index);

    // update stacks
    if(effectStacks[stacksIndex] == 255){
        overflowStacks[removedType];
    } else {
        effectStacks[stacksIndex]--;
    }
}

// COOLDOWN MANAGEMENT
void BattleUnit::decrementAllAbilityCooldowns(int amount){
    for(auto& ability : runtimeAbilities){
        ability.decrementCooldown(amount);
    }
}
void BattleUnit::decrementStatusDurations(int amount){
    size_t i = 0;
    while(i < activeEffects.size()){
        StatusEffect& effect = activeEffects[i];
        if(effect.decrementDuration(amount) == 0){
            removeStatusAtIndex(i);
        } else {
            i++;
        }
    }
}