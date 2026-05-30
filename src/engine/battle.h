#pragma once

#include "../entities/battleUnit.h"
#include "turnManager.h"
#include "abilities/effectContext.h"
#include "events/eventManager.h"
#include "events/eventListener.h"

#include <vector>
#include <memory>
#include <utility>

class BattleUnit;
// class EventListener;
// class DebugListener;

class Battle {
public:
    Battle(std::vector<std::unique_ptr<BattleUnit>> player, std::vector<std::unique_ptr<BattleUnit>> enemy);

    std::vector<BattleUnit*> getPlayerUnits();
    std::vector<BattleUnit*> getEnemyUnits();
    std::vector<BattleUnit*> getAllUnits();

    void startBattle();
    void advanceNextTurn();

    double getCurrentBattleTime() const;
    void publishEvent(CombatEvent& event) const;
    void addEventListener(EventListener* listener);

private:
    std::vector<std::unique_ptr<BattleUnit>> playerList;
    std::vector<std::unique_ptr<BattleUnit>> enemyList;
    double currentBattleTime = 0.0;

    EventManager eventManager;
    DebugListener debugListener;

    void performAttack(BattleUnit& attacker, BattleUnit& defender);
    void advanceBattleTime(double amount);
    bool isBattleOver() const;
};