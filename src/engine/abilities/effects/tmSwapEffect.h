#pragma once

#include "effectTypes.h"
#include "effectContext.h"

class BattleUnit;

class TMSwapEffect : public AbilityEffect {
public:
    TMSwapEffect(const Effects::TMSwapEffectData& d);

    void execute(EffectContext& c);
private:
};