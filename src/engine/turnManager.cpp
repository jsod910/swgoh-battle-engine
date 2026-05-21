#include <vector>
#include <limits>

#include "turnManager.h"
#include "../entities/statusEffect.h"
#include "../entities/battleUnit.h"

TurnManager::turnResult TurnManager::findTimeToNextTurn(const std::vector<BattleUnit*> units) {
    turnResult res;
    
    res.elapsedTime = std::numeric_limits<double>::max();
    res.nextUnit = nullptr;
    
    for(auto& unit : units){
        if(unit->isAlive()){
            if(unit->getEffectiveStat(ModifierStat::SPEED) > 0){
                double timeToTurn = (1000.0 - unit->getTurnMeter()) / unit->getEffectiveStat(ModifierStat::SPEED);
                
                if(timeToTurn < 0.0){
                    timeToTurn = 0.0;
                }

                if(timeToTurn < res.elapsedTime) {
                    res.elapsedTime = timeToTurn;
                    res.nextUnit = unit;
                }
            }
        }
    }

    return res;
}