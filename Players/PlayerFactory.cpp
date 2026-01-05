#include "PlayerFactory.h"
#include <memory>

// Maps to create Job and Character instances
const std::map<std::string, std::function<std::unique_ptr<Job>()>> PlayerFactory::jobMap = {
        {"Warrior", []() { return std::make_unique<Warrior>(); }},
        {"Archer", []() { return std::make_unique<Archer>(); }},
        {"Magician", []() { return std::make_unique<Magician>(); }}
};

const std::map<std::string, std::function<std::unique_ptr<Character>()>> PlayerFactory::characterMap = {
        {"RiskTaking", []() { return std::make_unique<RiskTaking>(); }},
        {"Responsible", []() { return std::make_unique<Responsible>(); }}
};

std::shared_ptr<Player> PlayerFactory::createPlayer(const std::string& playerName,
                                                    const std::string& playerJob,
                                                    const std::string& playerCharacter) {
    // Validate player name length
    if (playerName.length() < 3 || playerName.length() > 15) {
        throw InvalidPlayers();
    }

    // Find and create Job
    auto jobIter = jobMap.find(playerJob);
    if (jobIter == jobMap.end()) {
        throw InvalidPlayers();
    }
    std::unique_ptr<Job> jobPtr = jobIter->second();

    // Find and create Character
    auto characterIter = characterMap.find(playerCharacter);
    if (characterIter == characterMap.end()) {
        throw InvalidPlayers();
    }
    std::unique_ptr<Character> characterPtr = characterIter->second();

    // Create and return the Player object
    return std::make_shared<Player>(playerName, std::move(jobPtr), std::move(characterPtr));
}
