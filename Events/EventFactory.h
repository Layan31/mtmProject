#pragma once
#include <memory>
#include <vector>

#include "Event.h"
class EventFactory {

public:
    std::shared_ptr<Event> createEvent(const std::vector<string>& line);

};


class InvalidEvents : public std::exception{
    const char* what() const noexcept override {
        return "Invalid Events File";
    }
};

