#pragma once

#include "statusEffectDefinition.h"

#include <cstdint>

enum class StatusRemovalReason : uint8_t { EXPIRED, DISPELLED, CLEANSED };
enum class StatusEffectType : uint8_t; // name of statuseffect
enum class ModifierStat : uint8_t;  // stat category (speed, defense, etc.)
enum class StatusCategory : uint8_t; // { BUFF, DEBUFF, UNIQUE, LEADERSHIP, PASSIVE, OTHER }
class BattleUnit;

struct StatusEffectParams {
    const StatusEffectDefinition* def;
    
    BattleUnit* sourceUnit;
    int8_t duration;
    bool dispellable;
};
class StatusEffect {
public:
    StatusEffect(const StatusEffectParams& c) :
        statusDefinition(c.def),
        sourceUnit(c.sourceUnit),
        duration(c.duration),
        dispellable(c.dispellable)
    {}

    // MEMBER GETTERS
    StatusEffectType getName() const { return statusDefinition->getName(); }
    BattleUnit* getSourceUnitID() const { return sourceUnit; }
    StatusCategory getCategory() const { return statusDefinition->getCategory(); }
    
    const std::vector<StatusData::StatModifier>& getStatModifiers() const { return statusDefinition->getStatModifiers(); }

    int8_t getMaxStacks() const { return statusDefinition->getMaxStacks(); }
    int8_t getDuration() const { return duration; }
    void setDuration(int8_t dur) { duration = dur; }
    int8_t decrementDuration(int8_t amount) {
        if(duration < 0) return duration;
        if(duration < amount) return 0;
        
        if(duration > 0) duration -= amount;
        return duration;
    }
    bool isExpired() { return duration == 0; }
    
    bool isDispellable() const { return dispellable; }
    void setDispellable(bool disp) { dispellable = disp; }
private:
    const StatusEffectDefinition* statusDefinition;

    BattleUnit* sourceUnit;
    int8_t duration;   // -1 duration means infinite
    bool dispellable;
};
