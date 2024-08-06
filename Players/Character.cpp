#include "Character.h"
#include <algorithm> // For std::min

Character::~Character() = default;

Responsible::~Responsible() = default;

RiskTaking::~RiskTaking() = default;

int Responsible::playTurnWithPM(Player &pl) {
    int countPotions = 0;
    while (pl.getCoins() >= 5 && pl.getHealthPoints() < pl.getMaxHP()) {
        pl.setCoins(pl.getCoins() - 5);
        pl.setHP(std::min(pl.getMaxHP(), pl.getHealthPoints() + 10));
        countPotions++;
    }
    return countPotions;
}

int RiskTaking::playTurnWithPM(Player& pl) {
    if (pl.getHealthPoints() < 50 && pl.getCoins() >= 5) {
        pl.setCoins(pl.getCoins() - 5);
        pl.setHP(std::min(pl.getMaxHP(), pl.getHealthPoints() + 10));
        return 1;
    }
    return 0; // Return the number of potions bought
}

string Responsible::getCharacterType() const {
    return "Responsible";
}

string RiskTaking::getCharacterType() const {
    return "RiskTaking";
}
