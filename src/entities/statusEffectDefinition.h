#pragma once

#include "../../external/json/json_loader.hpp"

#include "enums/statusEffectType.h"
#include "enums/modifierStat.h"
#include "enums/statusCategory.h"
#include "enums/restriction.h"

#include <vector>
#include <cstdint>

// enum class StatusCategory : uint8_t;

using json = nlohmann::json;
namespace StatusData {
    struct StatModifier {
        double value;
        ModifierStat stat;
        ModifierType type;
    };
    inline void from_json(const json& j, StatModifier& d){
        if(j.contains("stat")){
            d.stat = modifierStatFromString(j.at("stat").get<std::string>());
        }
        if(j.contains("type")){
            if(j.at("type").get<std::string>() == "PERCENT") d.type = ModifierType::PERCENT;
            else d.type = ModifierType::FLAT;
        }
        if(j.contains("value")) d.value = j.at("value").get<double>();
    };

    struct StatusDefinitionParams {
        std::vector<StatModifier> modifiers;
        std::vector<Restriction> restrictions;

        StatusEffectType name;
        StatusCategory category;
        int8_t maxStacks = 1;
    };
    inline void from_json(const json& j, StatusDefinitionParams& d){
        if(j.contains("name")){
            d.name = statusFromString(j.at("name").get<std::string>());
        }
        if(j.contains("category")){
            d.category = statusCategoryFromString(j.at("category").get<std::string>());
        }
        if(j.contains("modifiers")){
            d.modifiers = j.at("modifiers").get<std::vector<StatModifier>>();
        }
        if(j.contains("restrictions")){
            for(const auto& r : j.at("restrictions")){
                d.restrictions.push_back(restrictionFromString(r.get<std::string>()));
            }
        }
        if(j.contains("max_stacks")) d.maxStacks = j.at("max_stacks").get<int8_t>();
    };
};

class StatusEffectDefinition {
public:
    StatusEffectDefinition(const StatusData::StatusDefinitionParams p);

    StatusEffectType getName() const;
    StatusCategory getCategory() const;
    const std::vector<StatusData::StatModifier>& getStatModifiers() const;
    const std::vector<Restriction>& getRestrictions() const;
    int8_t getMaxStacks() const;
private:
    StatusEffectType name;
    StatusCategory category;

    std::vector<StatusData::StatModifier> modifiers;
    std::vector<Restriction> restrictions;
    int8_t maxStacks;
};