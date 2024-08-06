#include "Event.h"

Event::Event(const std::string &name,int loot , int combatPower ,int damage ):
    eventName(name), loot(loot),combatPower(combatPower),damage(damage) {}