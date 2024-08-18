#pragma once

#include <string>
#include "Player.h"

class Player;
using std::string;

class Character {
public:
    virtual ~Character() = default;

    /**
     * Simulates a turn with a player
     *
     * @param pl - reference to the player
     * @return - result of the turn interaction
    */
    virtual int playTurnWithPM(Player &pl) = 0;

    /**
     * Gets the type of character
     *
     * @return - type of the character
    */
    virtual string getCharacterType() const = 0;
};


class Responsible : public Character {

public:
    virtual ~Responsible() = default;

    int playTurnWithPM(Player &pl) override;

    string getCharacterType() const override;
};


class RiskTaking : public Character {
public:
    virtual ~RiskTaking() = default;

    int playTurnWithPM(Player &pl) override;

    string getCharacterType() const override;
};
