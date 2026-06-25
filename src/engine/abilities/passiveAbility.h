#pragma once

#include <string>
#include <vector>
#include "../../entities/battleUnit.h"
#include "effects/abilityEffect.h"
#include "effects/effectContext.h"

class PassiveAbility {
public:
    std::vector<std::unique_ptr<AbilityEffect>> effects;

    PassiveAbility(std::string name);

    void cast(EffectContext& context) const;

    std::string getName() const;
private:
    std::string name;
    // std::string targetType;
};