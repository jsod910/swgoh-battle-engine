#pragma once

#include "../entities/battleUnit.h"
#include "turnManager.h"

#include <vector>
#include <memory>
#include <utility>

class Battle {
public:
    Battle(std::vector<std::unique_ptr<BattleUnit>> player, std::vector<std::unique_ptr<BattleUnit>> enemy);

    std::vector<BattleUnit*> getPlayerUnits();
    std::vector<BattleUnit*> getEnemyUnits();
    std::vector<BattleUnit*> getAllUnits();

    void startBattle();
    void advanceNextTurn();

    double getCurrentBattleTime() const;

private:
    std::vector<std::unique_ptr<BattleUnit>> playerList;
    std::vector<std::unique_ptr<BattleUnit>> enemyList;
    double currentBattleTime = 0.0;

    void performAttack(BattleUnit& attacker, BattleUnit& defender);
    void advanceBattleTime(double amount);
    bool isBattleOver() const;
};