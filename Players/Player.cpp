#include "Player.h"
#include "Job.h"
#include "Character.h"

Player::Player(const string& name, std::unique_ptr<Job> job, std::unique_ptr<Character> character)
    : name(name), playerJob(std::move(job)), playerCharacter(std::move(character)) {
    // Initialize player attributes
}

Player::Player() : name("Unnamed"), level(1), force(5), maxHP(100), currentHP(maxHP), coins(10) {
    // Default constructor
}

string Player::getDescription() const {
    // Ensure playerJob and playerCharacter are not null before dereferencing
    string jobName = playerJob ? playerJob->getJobName() : "Unknown";
    string charType = playerCharacter ? playerCharacter->getCharacterType() : "Unknown";

    return name + ", " + jobName + " with " + charType +
           " level " + std::to_string(level) + ", force " + std::to_string(force) + ")";
}

string Player::getName() const {
    return this->name;
}

int Player::getLevel() const {
    return this->level;
}

int Player::getForce() const {
    return this->force;
}

int Player::getHealthPoints() const {
    return this->currentHP;
}

int Player::getMaxHP() const {
    return this->maxHP;
}

int Player::getCoins() const {
    return this->coins;
}

Job* Player::getJob() const {
    return playerJob.get();
}

Character* Player::getCharacter() const {
    return playerCharacter.get();
}

void Player::setLevel(int level) {
    this->level = level;
}

void Player::setCoins(int coins) {
    this->coins = coins;
}

void Player::setHP(int hp) {
    this->currentHP = hp;
}

void Player::setForce(int force) {
    this->force = force;
}
