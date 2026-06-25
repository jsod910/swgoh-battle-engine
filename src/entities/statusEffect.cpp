#include "statusEffect.h"

StatusEffect::StatusEffect(const StatusEffectParams& c)
    :   type(c.type),
        category(c.category),
        targetStat(c.stat),
        modifierType(c.modType),
        modifierValue(c.modValue),
        duration(c.duration),
        dispellable(c.dispellable),
        maxStacks(c.maxStacks),
        sourceUnit(c.sourceUnit)
{}