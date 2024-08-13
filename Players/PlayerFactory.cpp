#include "PlayerFactory.h"
#include <memory>

std::shared_ptr<Player> PlayerFactory::createPlayer(const std::string& playerName,
                    const std::string& playerJob, const std::string& playerCharacter) {
    // Validate player name length
    if (playerName.length() < 3 || playerName.length() > 15) {
        throw InvalidPlayers();
    }

    // Define unique pointers for Job and Character
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
    if (playerCharacter == "RiskTaking") {
        characterPtr = std::make_unique<RiskTaking>();
    } else if (playerCharacter == "Responsible") {
        characterPtr = std::make_unique<Responsible>();
    } else {
        throw InvalidPlayers();
    }

    // Create and return the Player object
    return std::make_shared<Player>(playerName, std::move(jobPtr), std::move(characterPtr));
}
