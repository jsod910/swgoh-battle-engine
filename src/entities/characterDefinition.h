#pragma once

#include <string>
#include <vector>

#include "stats.h"
#include "abilityDefinition.h"

struct CharacterDefinition {
    std::string id;
    std::string name;

    statData::Stats baseStats;

    std::vector<std::string> abilityIds;
};