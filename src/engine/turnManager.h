#pragma once

#include "../entities/battleUnit.h"

#include <vector>

class TurnManager {
public:
    struct turnResult {
        double elapsedTime = 0.0;
        BattleUnit* nextUnit = nullptr;
    };

    static turnResult findTimeToNextTurn(const std::vector<BattleUnit*> units);
};