#include "statusEffectDefinition.h"

#include <vector>
#include <cstdint>
#include <utility>

StatusEffectDefinition::StatusEffectDefinition(const StatusData::StatusDefinitionParams p) :
    name(p.name),
    category(p.category),
    modifiers(std::move(p.modifiers)),
    maxStacks(p.maxStacks)
{}

StatusEffectType StatusEffectDefinition::getName() const {
    return name;
}

StatusCategory StatusEffectDefinition::getCategory() const {
    return category;
}

const std::vector<StatusData::StatModifier>& StatusEffectDefinition::getStatModifiers() const {
    return modifiers;
}

const std::vector<Restriction>& StatusEffectDefinition::getRestrictions() const {
    return restrictions;
}

int8_t StatusEffectDefinition::getMaxStacks() const {
    return maxStacks;
}