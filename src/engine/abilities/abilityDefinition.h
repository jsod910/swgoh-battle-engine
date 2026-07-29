#pragma once

#include <vector>
#include <string>

#include "../../entities/battleUnit.h"
#include "effects/abilityEffect.h"
#include "effects/effectContext.h"
#include "../../entities/enums/abilitySlot.h"

class AbilityEffect;
class BattleUnit;

class AbilityDefinition {
public:
    std::vector<std::unique_ptr<AbilityEffect>> effects;

    AbilityDefinition(std::string name, int baseCooldown, int initCooldown, AbilitySlot slot);

    void cast(EffectContext& context) const;

    std::string getName() const;
    int getBaseCooldown() const;
    int getInitCooldown() const;
    AbilitySlot getSlot() const;
private:
    std::string name;
    int baseCooldown;
    int initCooldown;
    AbilitySlot slot;
    // std::string targetType;
};