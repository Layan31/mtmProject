#include "PlayerFactory.h"
#include <memory>

std::shared_ptr<Player> PlayerFactory::createPlayer(const std::string& playerName,
                    const std::string& playerJob, const std::string& playerBehavior) {
    // Validate player name length
    if (playerName.length() < 3 || playerName.length() > 15) {
        throw InvalidPlayers();
    }

    // Define unique pointers for Job and Behavior
    std::unique_ptr<Job> jobPtr;
    std::unique_ptr<Character> characterPtr;

    // Determine the job type
    if (playerJob == "Warrior") {
        jobPtr = std::make_unique<Warrior>();
    } else if (playerJob == "Archer") {
        jobPtr = std::make_unique<Archer>();
    } else if (playerJob == "Magician") {
        jobPtr = std::make_unique<Magician>();
    } else {
        throw InvalidPlayers();
    }

    // Determine the character type
    if (playerBehavior == "RiskTaking") {
        characterPtr = std::make_unique<RiskTaking>();
    } else if (playerBehavior == "Responsible") {
        characterPtr = std::make_unique<Responsible>();
    } else {
        throw InvalidPlayers();
    }

    // Create and return the Player object
    return std::make_shared<Player>(playerName, std::move(jobPtr), std::move(characterPtr));
}
