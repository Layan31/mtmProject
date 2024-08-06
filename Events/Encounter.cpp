#include "Encounter.h"

string Encounter::getDescription() const {
    return "(power " + std::to_string(combatPower) +
           ", loot " + std::to_string(loot) +
           ", damage " + std::to_string(damage) + ")";
}

string Encounter::playTurn(Player& player) {
    unsigned int playerCP = player.getForce() + player.getLevel();
    if (player.getJob()->getCloseEncounter()) {
        player.setHP(std::max(0, player.getHealthPoints() - 10));
    }
    if (playerCP > this->combatPower) {
        player.setLevel(player.getLevel() + 1);
        player.setCoins(player.getCoins() + this->loot);
        return getEncounterWonMessage(player, this->loot);
    } else {
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
