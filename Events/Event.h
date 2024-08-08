#pragma once

#include "../Players/Player.h"

class Event {
protected:
    string eventName;
    unsigned int combatPower;
    unsigned int loot;
    unsigned int damage;

public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;

    virtual string playTurn(Player& player) = 0;


    Event(const std::string &name, unsigned int combatPower = 0, unsigned int loot = 0,
                        unsigned int damage = 0);
    virtual ~Event() = default;  // Virtual destructor for proper cleanup

    string getName() const { return eventName; }
    unsigned int getCombatPower() const { return combatPower; }
    unsigned int getLoot() const { return loot; }
    unsigned int getDamage() const { return damage; }

};
