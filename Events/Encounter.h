#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include "../Utilities.h"
#include "Event.h"

using std::string;
class Event;

class Encounter : public Event {

public:
    Encounter(const string& name = "", int loot = 0, int combatPower = 0,int damage = 0):
                Event(name,loot,combatPower,damage){}


    string getDescription() const override;

    string playTurn(Player& player) override;
};

class Balrog : public Encounter {
public:
    Balrog() : Encounter("Balrog", 15, 100, 9001) {}

    string getDescription() const override;
};

class Slime : public Encounter {
public:
    Slime() : Encounter("Slime", 12, 5, 25) {}

    string getDescription() const override;
};

class Snail : public Encounter {
public:
    Snail() : Encounter("Snail", 5, 2, 10) {}

    string getDescription() const override;
};

class Pack : public Encounter {
private:
    int pack_size;
    std::vector<Encounter> encounters;

public:

    Pack(const std::vector<Encounter>& pack1,int amount) {
        pack_size = amount;
        unsigned int sumForce = 0;
        unsigned int sumLoot=0;
        unsigned int sumDamage=0;
        for(const Encounter& b : pack1){
            sumForce+=b.getCombatPower();
            sumLoot+=b.getLoot();
            sumDamage+=b.getDamage();
        }
        loot=sumLoot;
        combatPower=sumForce;
        damage= sumDamage;
        encounters = pack1;
    }


    string getDescription() const override;

};
