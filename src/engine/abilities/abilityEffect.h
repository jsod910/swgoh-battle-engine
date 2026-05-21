#pragma once

#include "../../entities/battleUnit.h"

class BattleUnit;

enum class TargetType {
    SINGLE_ENEMY,
    AOE_ENEMY,
    SINGLE_ALLY,
    AOE_ALLY,
    SELF
};
inline const std::unordered_map<std::string, TargetType> stringToTargetTypeMap =
    {  
        {"SINGLE_ENEMY", TargetType::SINGLE_ENEMY},
        {"AOE_ENEMY", TargetType::AOE_ENEMY},
        {"SINGLE_ALLY", TargetType::SINGLE_ALLY},
        {"AOE_ALLY", TargetType::AOE_ALLY},
        {"SELF", TargetType::SELF}
    };

class AbilityEffect {
public:
    virtual ~AbilityEffect() = default;
    virtual void execute(BattleUnit* attacker, BattleUnit* target, const std::vector<BattleUnit*>& allUnits) = 0;
    TargetType getTargetType() const { return targetType; }
    void setTargetType(TargetType type) { targetType = type; }
protected:
    AbilityEffect(TargetType type) : targetType(type) {}

private:
    TargetType targetType;
};