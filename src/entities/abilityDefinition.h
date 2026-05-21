#pragma once

#include <string>

struct AbilityDefinition {
    std::string id;
    std::string name;

    // float damageMultiplier;
    int baseCooldown;
};

// struct BattleAbility {
//     AbilityDefinition* definition;

//     int currentCooldown;
// };