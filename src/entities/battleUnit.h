#pragma once

#include "characterDefinition.h"
#include "stats.h"
#include "../loaders/characterCache.h"
#include "battleAbility.h"
#include "statusEffect.h"
#include "../engine/abilities/effects/effectContext.h"
#include "enums/statusEffectType.h"

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
    void takeTurn();

    // DYNAMIC ATTRBIUTES
    double getEffectiveStat(ModifierStat type) const;
    int getCurrentHealth() const;
    int getCurrentProtection() const;
    double getTurnMeter() const;
    void advanceTurnMeter(double amount);
    bool isAlive() const;
    void takeDamage(int amount);
    void recoverHealth(int amount);
    void recoverProtection(int amount);
    void tickCooldowns();

    // ABILITIES
    void executeAbility(size_t idx, EffectContext& context);
    size_t chooseBestAbility() const;
    void decrementAllAbilityCooldowns(int amount = 1);
    void resetAllAbilityCooldowns();
    void decrementAbilityCooldown(BattleAbility& ability, int amount = 1);
    void resetAbilityCooldown(BattleAbility& ability);

    // STATUS EFFECTS
    bool hasStatus(StatusEffectType type) const;
    void applyStatus(const StatusEffect& effect);
    int removeAllStatus(StatusCategory type);   // returns no. of status effects removed

    
private:
    const CharacterDefinition* character;
    Team teamID;

    statData::Stats enterBattleStats;
    std::vector<StatusEffect> activeEffects;
    std::array<uint8_t, static_cast<size_t>(StatusEffectType::COUNT)> effectStacks = {};
    std::unordered_map<StatusEffectType, int> overflowStacks;
    // std::uint64_t statusMask = 0;

    struct CurrentViability {
        int health;
        int protection; 
    } currentViability;
    double turnMeter;

    std::vector<BattleAbility> runtimeAbilities;

    
    // constexpr std::uint64_t getStatusBit(StatusEffectType type) const {
    //     switch(type){
    //         case StatusEffectType::STUN: return 1ULL << 0;
    //         case StatusEffectType::DAZE: return 1ULL << 1;
    //         case StatusEffectType::TAUNT: return 1ULL << 2;
    //         case StatusEffectType::DAMAGE_IMMUNITY: return 1ULL << 3;
            
    //         default: return 0;
    //     }
    // }
    int getEffectStacks(StatusEffectType type) const;
    void addEffectStacks(StatusEffectType type, int amount = 1);
    void removeStatusAtIndex(size_t index);
    
    void decrementStatusDurations(int amount = 1);
};