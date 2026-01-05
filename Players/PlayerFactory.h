#pragma once
#include <memory>
#include "Player.h"
#include <map>
#include <functional>


class PlayerFactory {
    static const std::map<std::string, std::function<std::unique_ptr<Job>()>> jobMap;
    static const std::map<std::string, std::function<std::unique_ptr<Character>()>> characterMap;
public:
    std::shared_ptr<Player> createPlayer(const string& name, const string& job,
                                         const string& behave);
};

class InvalidPlayers : public std::exception{
    const char* what() const noexcept override {
        return "Invalid Players File";
    }
};