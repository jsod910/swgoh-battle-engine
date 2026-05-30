#pragma once

#include "characterDefinition.h"
#include "stats.h"
#include "../loaders/characterCache.h"
#include "battleAbility.h"
#include "statusEffect.h"
#include "../engine/abilities/effectContext.h"

#include <string>
#include <vector>
#include <memory>

class CharacterCache;
class BattleAbility;

enum class Team {
    PLAYER,
    ENEMY
};

class BattleUnit {
public:
    BattleUnit(CharacterCache& cache, const std::string& charID, Team teamID);

    std::string getName() const;
    Team getTeamID() const;

    double getEffectiveStat(ModifierStat type) const;
    int getCurrentHealth() const;
    int getCurrentProtection() const;
    double getTurnMeter() const;

    bool isAlive() const;
    void advanceTurnMeter(double amount);
    void takeTurn();
    void takeDamage(int amount);
    void recoverHealth(int amount);
    void recoverProtection(int amount);
    void executeAbility(size_t idx, EffectContext& context);

    size_t chooseBestAbility() const;

private:
    const CharacterDefinition* character;
    Team teamID;

    statData::Stats enterBattleStats;
    std::vector<StatusEffect> activeEffects;

    struct CurrentViability {
        int health;
        int protection; 
    } currentViability;
    double turnMeter;

    std::vector<BattleAbility> runtimeAbilities;
};


// struct BattleUnit {
//     const CharacterDefinition* character;
//     // int teamID;

//     Stats enterBattleStats;
//     struct CurrentViability {
//         int health;
//         int protection = 0;
//     } currentViability;
//     // struct CurrentModifiers {
//     //     double offense;
//     //     double speed;
//     // } currentModifiers;

//     float turnMeter;
//     void takeTurn(){
//         turnMeter -= 1000.0f;
//     }

//     BattleUnit(const CharacterDefinition* charDef)
//         : character(charDef)
//     {
//         initializeBattleState();
//     }

//     void initializeBattleState(){
//         enterBattleStats = character->baseStats;

//         currentViability.health = enterBattleStats.health;
//         // currentViability.protection = enterBattleStats.protection;

//         turnMeter = 0.0f;
//     }

//     bool isAlive() const {
//         return currentViability.health > 0;
//     }
// };