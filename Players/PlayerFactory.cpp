#include "PlayerFactory.h"

#include <memory>

std::shared_ptr<Player> PlayerFactory::createPlayer(const string& name,
                                                    const string& job,const string& behaviour){
    if(name.size() > 15 || name.size() < 3){
        throw InvalidPlayers();
    }

    if(job == "Warrior"){
        if(behaviour == "RiskTaking"){
            return std::make_shared<Player>(name, std::make_unique<Warrior>(),
                std::make_unique<RiskTaking>());
        }
        if ( behaviour == "Responsible") {
            return std::make_shared<Player>(name, std::make_unique<Warrior>(),
                std::make_unique<Responsible>());
        }

        throw InvalidPlayers();
    }
    if(job == "Archer"){
        if(behaviour == "RiskTaking"){
            return std::make_shared<Player>(name, std::make_unique<Archer>(),
                std::make_unique<RiskTaking>());
        }
        if ( behaviour == "Responsible") {
            return std::make_shared<Player>(name, std::make_unique<Archer>(),
                std::make_unique<Responsible>());
        }

        throw InvalidPlayers();
    }
    if(job == "Magician"){
        if(behaviour == "RiskTaking"){
            return std::make_shared<Player>(name, std::make_unique<Magician>(),
                std::make_unique<RiskTaking>());
        }
        if ( behaviour == "Responsible") {
            return std::make_shared<Player>(name, std::make_unique<Magician>(),
                std::make_unique<Responsible>());
        }

        throw InvalidPlayers();
    }
    throw InvalidPlayers();
}
