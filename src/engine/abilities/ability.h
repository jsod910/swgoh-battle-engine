#pragma once

#include <vector>
#include <string>

#include "../../entities/battleUnit.h"
#include "effects/abilityEffect.h"
#include "effects/effectContext.h"

class AbilityEffect;
class BattleUnit;

class ActiveAbility {
public:
    std::vector<std::unique_ptr<AbilityEffect>> effects;

    ActiveAbility(std::string name, int baseCooldown, int initCooldown);

    void cast(EffectContext& context) const;

    std::string getName() const;
    int getBaseCooldown() const;
    int getInitCooldown() const;
private:
    std::string name;
    int baseCooldown;
    int initCooldown;
    // std::string targetType;
};