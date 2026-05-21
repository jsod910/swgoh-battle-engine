#pragma once

#include <string>

enum class ModifierStat {
    MASTERY,

    HEALTH,
    PROTECTION,
    SPEED,
    CRIT_DAMAGE,
    POTENCY,
    TENACITY,
    HEALTH_STEAL,
    DEFENSE_PEN,
    
    PHYS_OFFENSE,
    PHYS_CRIT_CHANCE,
    ARMOR_PEN,
    PHYS_ACCURACY,

    FLAT_ARMOR,
    DODGE,
    CRIT_AVOIDANCE,
    
    SPEC_OFFENSE,
    SPEC_CRIT_CHANCE,
    RESISTANCE_PEN,
    SPEC_ACCURACY,

    FLAT_RESISTANCE,
    DEFLECTION
};
inline const std::unordered_map<std::string, ModifierStat> stringToModifierStatMap =
    {  
        {"MASTERY", ModifierStat::MASTERY},
        {"HEALTH", ModifierStat::HEALTH},
        {"PROTECTION", ModifierStat::PROTECTION},
        {"SPEED", ModifierStat::SPEED},
        {"CRIT_DAMAGE", ModifierStat::CRIT_DAMAGE},
        {"POTENCY", ModifierStat::POTENCY},
        {"TENACITY", ModifierStat::TENACITY},
        {"HEALTH_STEAL", ModifierStat::HEALTH_STEAL},
        {"DEFENSE_PEN", ModifierStat::DEFENSE_PEN},
        {"PHYS_OFFENSE", ModifierStat::PHYS_OFFENSE},
        {"PHYS_CRIT_CHANCE", ModifierStat::PHYS_CRIT_CHANCE},
        {"ARMOR_PEN", ModifierStat::ARMOR_PEN},
        {"PHYS_ACCURACY", ModifierStat::PHYS_ACCURACY},
        {"FLAT_ARMOR", ModifierStat::FLAT_ARMOR},
        {"DODGE", ModifierStat::DODGE},
        {"CRIT_AVOIDANCE", ModifierStat::CRIT_AVOIDANCE},
        {"SPEC_OFFENSE", ModifierStat::SPEC_OFFENSE},
        {"SPEC_CRIT_CHANCE", ModifierStat::SPEC_CRIT_CHANCE},
        {"RESISTANCE_PEN", ModifierStat::RESISTANCE_PEN},
        {"SPEC_ACCURACY", ModifierStat::SPEC_ACCURACY},
        {"FLAT_RESISTANCE", ModifierStat::FLAT_RESISTANCE},
        {"DEFLECTION", ModifierStat::DEFLECTION}
    };

enum class EffectType { BUFF, DEBUFF, LEADERSHIP, PASSIVE };
enum class ModifierType { FLAT, PERCENT };

class StatusEffect {
public:
    StatusEffect(std::string id, EffectType type, ModifierStat stat, ModifierType modType,
        double modValue, int duration, bool dispellable, std::string sourceUnitID, int stacks,
        int maxStats);

    std::string getID() const { return effectID; }
    std::string getSourceUnitID() const { return sourceUnitID; }

    EffectType getType() const { return type; }
    ModifierStat getStat() const { return targetStat; }
    ModifierType getModType() const { return modifierType; }
    double getModValue() const { return modifierValue; }

    int getDuration() const { return duration; }
    void reduceDuration() { if (duration > 0) duration--; }
    bool isExpired() { return duration == 0; }
    bool isDispellable() const { return dispellable; }
private:
    EffectType type;
    ModifierStat targetStat;
    ModifierType modifierType;
    double modifierValue;
    
    int duration;   // -1 duration means infinite
    bool dispellable;

    std::string effectID;
    std::string sourceUnitID;
    int maxStacks;  // -1 maxStacks means no limit
};