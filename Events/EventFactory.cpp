#include "EventFactory.h"
#include <memory>
#include "SpecialEvent.h"
#include "Encounter.h"
#include <vector>
#include <map>
#include <functional>

std::shared_ptr<Event> EventFactory::createEvent(const std::vector<std::string>& inputLines) {
    // Map for creating specific Encounter events
    static const std::map<std::string, std::function<std::shared_ptr<Encounter>()>> encounterMap = {
        {"Balrog", []() { return std::make_shared<Balrog>(); }},
        {"Slime", []() { return std::make_shared<Slime>(); }},
        {"Snail", []() { return std::make_shared<Snail>(); }}
    };

    // Map for creating specific SpecialEvent events
    static const std::map<std::string, std::function<std::shared_ptr<Event>()>> specialEventMap = {
        {"SolarEclipse", []() { return std::make_shared<SolarEclips>(); }},
        {"PotionsMerchant", []() { return std::make_shared<PotionsMerchant>(); }}
    };

    // Handle "Pack" event
    if (inputLines[0] == "Pack") {
        int quantity = std::stoi(inputLines[1]);
        std::vector<Encounter> encounters;

        // Create encounters based on the input provided
        for (size_t index = 2; index < inputLines.size(); ++index) {
            const auto& creature = inputLines[index];
            auto encounterIter = encounterMap.find(creature);
            if (encounterIter != encounterMap.end()) {
                encounters.push_back(*encounterIter->second());
            } else {
                throw InvalidEvents();
            }
        }

        return std::make_shared<Pack>(encounters, quantity);
    }

    // Create specific events
    auto encounterIter = encounterMap.find(inputLines[0]);
    if (encounterIter != encounterMap.end()) {
        return encounterIter->second();
    }

    auto specialEventIter = specialEventMap.find(inputLines[0]);
    if (specialEventIter != specialEventMap.end()) {
        return specialEventIter->second();
    }

    // Throw an exception for invalid event types
    throw InvalidEvents();
}
