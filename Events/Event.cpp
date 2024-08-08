#include "Event.h"

Event::Event(const std::string &name, unsigned int combatPower, unsigned int loot,
                        unsigned int damage):
    eventName(name), combatPower(combatPower), loot(loot), damage(damage) {}