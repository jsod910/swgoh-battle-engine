#include "eventListener.h"
#include "eventTypes.h"

#include <iostream>

void DebugListener::onEvent(const CombatEvent& event) {
    std::cout << "\nEvent Logged" << std::endl;
}