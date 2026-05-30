#pragma once

#include "eventTypes.h"

class Battle;

class EventListener {
public:
    virtual ~EventListener() = default;

    virtual void onEvent(const CombatEvent& event) = 0;
private:
};

class DebugListener : public EventListener {
public:    
    void onEvent(const CombatEvent& event) override;
};