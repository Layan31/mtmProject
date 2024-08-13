#pragma once
#include <memory>
#include "Player.h"


class PlayerFactory {
public:
    std::shared_ptr<Player> createPlayer(const string& name, const string& job,
                                         const string& behave);
};

class InvalidPlayers : public std::exception{
    const char* what() const noexcept override {
        return "Invalid Players File";
    }
};