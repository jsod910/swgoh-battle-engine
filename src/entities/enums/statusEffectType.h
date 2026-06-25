#pragma once

#include "../statusEffect.h"

#include <string>
#include <cstdint>

enum class StatusEffectType : uint8_t {
    #define X(name) name,

    #include "statusEffectType.def"

    #undef X

        COUNT
};

StatusEffectType statusFromString(const std::string& str);
const std::string statusToString(StatusEffectType type);

constexpr StatusCategory getStatusCategory(StatusEffectType type){
    switch(type){
        case StatusEffectType::OFFENSE_UP:
        case StatusEffectType::DEFENSE_UP:
        case StatusEffectType::CRIT_DAMAGE_UP:
        case StatusEffectType::SPEED_UP:
            return StatusCategory::BUFF;

        case StatusEffectType::STUN:
        case StatusEffectType::OFFENSE_DOWN:
        case StatusEffectType::DEFENSE_DOWN:
        case StatusEffectType::SPEED_DOWN:
            return StatusCategory::DEBUFF;

        default:
            return StatusCategory::OTHER;
    }
}