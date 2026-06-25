#pragma once

#include <string>
#include <unordered_map>
#include <cstdint>

enum class ModifierStat : uint8_t {
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
    DEFLECTION,

    COUNT,
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

enum class StatusCategory { BUFF, DEBUFF, UNIQUE, LEADERSHIP, PASSIVE, OTHER };
enum class ModifierType { FLAT, PERCENT };
enum class StatusRemovalReason { EXPIRED, DISPELLED, CLEANSED };
enum class StatusEffectType : uint8_t;
class BattleUnit;
struct StatusEffectParams {
    StatusEffectType type;
    StatusCategory category;
    ModifierStat stat;
    ModifierType modType;
    double modValue;
    int duration;
    bool dispellable;
    BattleUnit* sourceUnit;
    int maxStacks;
};

class StatusEffect {
public:
    StatusEffect(const StatusEffectParams& c);


    // MEMBER GETTERS
    StatusEffectType getType() const { return type; }
    BattleUnit* getSourceUnitID() const { return sourceUnit; }
    StatusCategory getCategory() const { return category; }
    ModifierStat getStat() const { return targetStat; }
    ModifierType getModType() const { return modifierType; }
    double getModValue() const { return modifierValue; }

    int getDuration() const { return duration; }
    void setDuration(int dur) { duration = dur; }
    int decrementDuration(int amount) {
        if (duration > 0) duration -= amount;
        return duration;
    }
    bool isExpired() { return duration == 0; }
    
    bool isDispellable() const { return dispellable; }
    void setDispellable(bool disp) { dispellable = disp; }
    int getMaxStacks() const { return maxStacks; }
private:
    StatusEffectType type;
    StatusCategory category;

    ModifierStat targetStat;
    ModifierType modifierType;
    double modifierValue;
    
    int duration;   // -1 duration means infinite
    bool dispellable;
    int maxStacks;  // -1 maxStacks means no limit

    // std::string effectID;
    BattleUnit* sourceUnit;
};
