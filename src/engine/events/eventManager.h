#pragma once

#include "eventTypes.h"
#include "listeners/eventListener.h"

#include <vector>

struct CombatEvent;
class EventListener;

class EventManager {
public:
    void publish(const CombatEvent& event) const;
    void subscribe(EventListener* listener);
private:
    std::vector<EventListener*> listeners;
};