#include "EventFactory.h"
#include <memory>
#include "SpecialEvent.h"
#include "Event.h"
#include "Encounter.h"
#include <vector>

std::shared_ptr<Event> EventFactory::createEvent(const std::vector<std::string>& inputLines) {
    // Check if the event type is Pack
    if (inputLines[0] == "Pack") {
        int quantity = std::stoi(inputLines[1]);
        std::vector<Encounter> encounters;

        // Create encounters based on the input provided
        for (size_t index = 2; index < inputLines.size(); ++index) {
            const auto& creature = inputLines[index];
            if (creature == "Balrog") {
                encounters.emplace_back(Balrog());
            } else if (creature == "Slime") {
                encounters.emplace_back(Slime());
            } else if (creature == "Snail") {
                encounters.emplace_back(Snail());
            }
        }

        return std::make_shared<Pack>(encounters, quantity);
    }

    // Create specific event types based on the input
    if (inputLines[0] == "Balrog") {
        return std::make_shared<Balrog>();
    }
    if (inputLines[0] == "Snail") {
        return std::make_shared<Snail>();
    }
    if (inputLines[0] == "Slime") {
        return std::make_shared<Slime>();
    }
    if (inputLines[0] == "SolarEclipse") {
        return std::make_shared<SolarEclips>();
    }
    if (inputLines[0] == "PotionsMerchant") {
        return std::make_shared<PotionsMerchant>();
    }

    // Throw an exception for invalid event types
    throw InvalidEvents();
}
