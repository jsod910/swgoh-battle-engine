#include "eventManager.h"
#include "eventListener.h"
#include "eventTypes.h"

void EventManager::publish(const CombatEvent& event) const {
    for(auto* listener : listeners){
        listener->onEvent(event);
    }
}

void EventManager::subscribe(EventListener* listener){
    listeners.push_back(listener);
}