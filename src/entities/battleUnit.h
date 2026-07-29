#pragma once

#include "characterDefinition.h"
#include "stats.h"
#include "../loaders/characterCache.h"
#include "battleAbility.h"
#include "statusEffect.h"
#include "../engine/abilities/effects/effectContext.h"
#include "enums/statusEffectType.h"
#include "enums/restriction.h"
#include "enums/abilitySlot.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include <array>
#include <utility>

class CharacterCache;
class BattleAbility;

enum class Team {
    PLAYER,
    ENEMY
};

class BattleUnit {
public:
    // CONSTRUCTOR
    BattleUnit(CharacterCache& cache, const std::string& charID, Team teamID);

    // STATIC ATTRIBUTES
    std::string getName() const;
    Team getTeamID() const;
    void startTurn();
    void endTurn();

    // DYNAMIC ATTRBIUTES
    double getEffectiveStat(ModifierStat stat) const;
    int getCurrentHealth() const;
    int getCurrentProtection() const;
    double getTurnMeter() const;
    void advanceTurnMeter(double amount);
    bool modifyTurnMeter(double amount);
    void setTurnMeter(double amount);
    bool isAlive() const;
    void takeDamage(int amount);
    int recoverViability(ModifierStat stat, int amount);
    void tickCooldowns();

    // ABILITIES
    void executeAbility(size_t idx, EffectContext& context);
    size_t chooseBestAbility() const;
    void decrementAllAbilityCooldowns(int amount = 1);
    void resetAllAbilityCooldowns();
    void resetAbilityCooldown(AbilitySlot slot);
    void decrementAbilityCooldown(AbilitySlot slot, int amount = 1);
    void resetAbilityCooldown(BattleAbility& ability);

    // STATUS EFFECTS
    bool hasStatus(StatusEffectType type) const;
    void applyStatus(const StatusEffectParams& params);
    int removeAllStatus(StatusCategory type);   // returns no. of status effects removed

    
private:
    const CharacterDefinition* character;
    Team teamID;

    statData::Stats enterBattleStats;
    std::vector<StatusEffect> activeEffects;
    std::array<uint8_t, static_cast<size_t>(StatusEffectType::COUNT)> effectStacks = {};
    std::unordered_map<StatusEffectType, int> overflowStacks;
    std::array<uint8_t, static_cast<size_t>(Restriction::COUNT)> restrictions = {};
    
    struct CachedModifiers {
        std::array<double, static_cast<size_t>(ModifierStat::COUNT)> percent{};
        std::array<double, static_cast<size_t>(ModifierStat::COUNT)> flat{};
    } cachedModifiers;

    struct CurrentViability {
        int health;
        int protection; 
    } currentViability;
    
    double turnMeter;
    std::vector<BattleAbility> runtimeAbilities;

    int getEffectStacks(StatusEffectType type) const;
    void addEffectStacks(StatusEffectType type, int amount = 1);
    void removeStatusAtIndex(size_t index);
    void decrementStatusDurations(int amount = 1);
    
    void updateCachedModifier(ModifierStat stat, ModifierType type, double val);
    double getCachedModifier(ModifierStat stat, ModifierType type) const;

    void addRestrictionCount(Restriction r);
    void removeRestrictionCount(Restriction r);
    uint8_t getRestrictionCount(Restriction r) const;
};