#pragma once

#include "../../../../external/json/json_loader.hpp"
#include "../../../entities/statusEffect.h"
#include "abilityEffect.h"
#include "damageTypes.h"
#include "../../../utils/enumUtils.h"

#include "../../../entities/enums/statusEffectType.h"
#include "../../../entities/enums/modifierStat.h"
#include "../../../entities/enums/targetType.h"
#include "../../../entities/enums/cooldownMode.h"
#include "../../../entities/enums/abilitySlot.h"

using json = nlohmann::json;

namespace Effects {

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
            d.targetType = targetTypeFromString(j.at("targetType").get<std::string>());
        }
        if(j.contains("offenseStat")){
            d.offense = modifierStatFromString(j.at("offenseStat").get<std::string>());
        }
        if(j.contains("defenseStat")){
            d.defense = modifierStatFromString(j.at("defenseStat").get<std::string>());
        }
        if(j.contains("multiplier")) { d.multiplier = j.at("multiplier").get<double>(); }
        if(j.contains("canEvade")) { d.canEvade = j.at("canEvade").get<bool>(); }
        if(j.contains("canCrit")) { d.canCrit = j.at("canCrit").get<bool>(); }
        if(j.contains("ignoreDefense")) { d.ignoreDefense = j.at("ignoreDefense").get<bool>(); }
    };

  
    struct ApplyStatusEffectData {
        StatusEffectType name;
        TargetType targetType = TargetType::SINGLE_ENEMY;
        
        double chance = 1.0;

        int duration = 1;
        bool canEvade = true;
        bool canDispel = true;
        bool canResist = true;
    };
    inline void from_json(const json& j, ApplyStatusEffectData& d) {
        if(j.contains("statusEffectType")){
            d.name = statusFromString(j.at("statusEffectType").get<std::string>());
        }
        if(j.contains("targetType")){
            d.targetType = targetTypeFromString(j.at("targetType").get<std::string>());
        }
        if(j.contains("chance")) { d.chance = j.at("chance").get<double>(); }
        if(j.contains("duration")) { d.duration = j.at("duration").get<int>(); }
        if(j.contains("canEvade")) { d.canEvade = j.at("canEvade").get<bool>(); }
        if(j.contains("canDispel")) { d.canDispel = j.at("canDispel").get<bool>(); }
        if(j.contains("canResist")) { d.canResist = j.at("canResist").get<bool>(); }
    };


    struct RecoverEffectData {
        TargetType targetType;
        ModifierStat stat;
        bool equalize = false;
        
        ModifierType modType = ModifierType::PERCENT;
        double value = 0.0;
    };
    inline void from_json(const json& j, RecoverEffectData& d){
        if(j.contains("targetType")){
            d.targetType = targetTypeFromString(j.at("targetType").get<std::string>());
        }
        if(j.contains("recoverStat")){
            d.stat = modifierStatFromString(j.at("recoverStat").get<std::string>());
        }
        if(j.contains("modType")){
            if(j.at("modType").get<std::string>() == "PERCENT") d.modType = ModifierType::PERCENT;
            else d.modType = ModifierType::FLAT;
        }
        if(j.contains("value")) { d.value = j.at("value").get<double>(); }
        if(j.contains("equalize")) { d.equalize = true; }
    };


    struct TMManipulationData {
        TargetType targetType;
        
        double chance = 1.0;
        double value;
    };
    inline void from_json(const json& j, TMManipulationData& d){
        if(j.contains("targetType")){
            d.targetType = targetTypeFromString(j.at("targetType").get<std::string>());
        }
        if(j.contains("chance")) { d.chance = j.at("chance").get<double>(); }
        if(j.contains("value")) { d.value = j.at("value").get<double>(); }
    };


    struct ModifyCooldownEffectData {
        TargetType targetType;

        double chance = 1.0;
        AbilitySlot slot = AbilitySlot::ALL;
        int8_t amount = 0;
        CooldownMode mode;

    };
    inline void from_json(const json& j, ModifyCooldownEffectData& d){
        if(j.contains("targetType")){
            d.targetType = targetTypeFromString(j.at("targetType").get<std::string>());
        }
        if(j.contains("chance")) { d.chance = j.at("chance").get<double>(); }
        if(j.contains("slot")){
            d.slot = abilitySlotFromString(j.at("slot").get<std::string>());
        }
        if(j.contains("value")){
            d.amount = static_cast<int8_t>(j.at("value").get<int>());
        }
        if(j.contains("mode")){
            d.mode = cooldownModeFromString(j.at("mode").get<std::string>());
        }
    };

    struct TMSwapEffectData {
        TargetType targetType;
    };
    inline void from_json(const json& j, TMSwapEffectData& d){
        if(j.contains("targetType")){
            d.targetType = targetTypeFromString(j.at("targetType").get<std::string>());
        }
    };
};