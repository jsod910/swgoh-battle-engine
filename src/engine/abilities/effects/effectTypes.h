#pragma once

#include "../../../../external/json/json_loader.hpp"
#include "../../../entities/statusEffect.h"
#include "abilityEffect.h"
#include "damageTypes.h"
#include "../../../utils/enumUtils.h"
#include "../../../entities/enums/statusEffectType.h"
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
        ModifierStat offense = ModifierStat::PHYS_OFFENSE;
        ModifierStat defense = ModifierStat::FLAT_ARMOR;

        double multiplier = 1.0;

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
        if(j.contains("offenseStat")){
            d.offense = parseEnum(j.at("offenseStat").get<std::string>(), stringToModifierStatMap);
        }
        if(j.contains("defenseStat")){
            d.defense = parseEnum(j.at("defenseStat").get<std::string>(), stringToModifierStatMap);
        }
        if(j.contains("multiplier")) { d.multiplier = j.at("multiplier").get<double>(); }
        if(j.contains("canEvade")) { d.canEvade = j.at("canEvade").get<bool>(); }
        if(j.contains("canCrit")) { d.canCrit = j.at("canCrit").get<bool>(); }
        if(j.contains("ignoreDefense")) { d.ignoreDefense = j.at("ignoreDefense").get<bool>(); }
    };

  
    struct ApplyStatusEffectData {
        StatusEffectType statusEffectType;
        TargetType targetType = TargetType::SINGLE_ENEMY;
        
        int duration = 1;
        bool canEvade = true;
        bool canDispel = true;
        bool canResist = true;
    };
    inline void from_json(const json& j, ApplyStatusEffectData& d) {
        if(j.contains("statusEffectType")){
            d.statusEffectType = statusFromString(j.at("statusEffectType").get<std::string>());
        }
        if(j.contains("targetType")){
            d.targetType = parseEnum(j.at("targetType").get<std::string>(), stringToTargetTypeMap);
        }
        if(j.contains("duration")) { d.duration = j.at("duration").get<int>(); }
        if(j.contains("canEvade")) { d.canEvade = j.at("canEvade").get<bool>(); }
        if(j.contains("canDispel")) { d.canDispel = j.at("canDispel").get<bool>(); }
        if(j.contains("canResist")) { d.canResist = j.at("canResist").get<bool>(); }
    };  

};