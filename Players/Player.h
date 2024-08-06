#pragma once

#include <memory>
#include <string>
#include "Job.h"
#include "Character.h"

class Character;
using std::string;

class Player {
private:
    string name;
    int level;
    int force;
    int maxHP;
    int currentHP;
    int coins;
    std::shared_ptr<Job> playerJob;
    std::shared_ptr<Character> playerCharacter;


public:
     Player(const string& name, std::unique_ptr<Job> job, std::unique_ptr<Character> character);

     /**
     * Default constructor for Player class
     */
     Player();

      /**
     * Destructor for Player class
     */
     ~Player() = default;
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    int getMaxHP() const;

    Job* getJob() const;

    Character* getCharacter() const;

    void setLevel(int level);

    void setCoins(int coins);

    void setHP(int hp);

    void setForce(int force);
};
