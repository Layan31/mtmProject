#include "Encounter.h"

string Encounter::getDescription() const {
    return "(power " + std::to_string(combatPower) +
           ", loot " + std::to_string(loot) +
           ", damage " + std::to_string(damage) + ")";
}

string Encounter::playTurn(Player& player) {
    unsigned int playerCP;
    if(player.getJob()->getJobName() == "Warrior") {
        playerCP = player.getForce() * 2 + player.getLevel();
    } else {
        playerCP = player.getForce() + player.getLevel();
    }
    if (playerCP >= this->combatPower) {
        if(eventName == "Balrog") {
            combatPower += 2;
        }
        player.setLevel(player.getLevel() + 1);
        player.setCoins(player.getCoins() + (int)this->loot);
        if (player.getJob()->getCloseEncounter()) {
            player.setHP(std::max(0, player.getHealthPoints() - 10));
        }
        return getEncounterWonMessage(player, this->loot);
    } else {
        if(eventName == "Balrog") {
            combatPower += 2;
        }
        player.setHP(std::max(0, (int)(player.getHealthPoints() - this->damage)));
        return getEncounterLostMessage(player, this->damage);
    }
}

string Balrog::getDescription() const {
    return "Balrog " + Encounter::getDescription();
}

string Slime::getDescription() const {
    return "Slime " + Encounter::getDescription();
}

string Snail::getDescription() const {
    return "Snail " + Encounter::getDescription();
}

string Pack::getDescription() const {
    return "Pack of " + std::to_string(encounters.size()) + " members " + Encounter::getDescription();
}
