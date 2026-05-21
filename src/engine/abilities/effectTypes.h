#pragma once

#include "../../../external/json/json_loader.hpp"
#include "../../entities/statusEffect.h"
#include "abilityEffect.h"
#include "damageTypes.h"
#include "../../utils/enumUtils.h"
using json = nlohmann::json;

namespace Effects {
    
    enum class AbilityEffectType { DAMAGE, HEAL, APPLY_STATUS };
    inline const std::unordered_map<std::string, AbilityEffectType> stringToAbilityEffectTypeMap =
        {  
            {"DAMAGE", AbilityEffectType::DAMAGE},
            {"HEAL", AbilityEffectType::HEAL},
            {"APPLY_STATUS", AbilityEffectType::APPLY_STATUS}
        };

    struct DamageEffectData {
        DamageType damageType = DamageType::REGULAR;
        TargetType targetType = TargetType::SINGLE_ENEMY;
        ModifierStat offense;
        ModifierStat defense = ModifierStat::FLAT_ARMOR;

        double multiplier;

        bool canEvade = true;
        bool canCrit = true;
        bool ignoreDefense = false;
    };
    inline void from_json(const json& j, DamageEffectData& d) {
        if(j.contains("damageType")){
            d.damageType = parseEnum(j.at("damageType").get<std::string>(), stringToDamageTypeMap);
        }
        if(j.contains("targetType")){
            d.targetType = parseEnum(j.at("targetType").get<std::string>(), stringToTargetTypeMap);
        }
        d.offense = parseEnum(j.at("offenseStat").get<std::string>(), stringToModifierStatMap);
        d.defense = parseEnum(j.at("defenseStat").get<std::string>(), stringToModifierStatMap);
        d.multiplier = j.at("multiplier").get<double>();

        if(j.contains("canEvade")) { d.canEvade = j.at("canEvade").get<bool>(); }
        if(j.contains("canCrit")) { d.canCrit = j.at("canCrit").get<bool>(); }
        if(j.contains("ignoreDefense")) { d.ignoreDefense = j.at("ignoreDefense").get<bool>(); }
    };

};