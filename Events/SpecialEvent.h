#pragma once
#include "SpecialEvent.h"
#include "../Utilities.h"

class Event;

class SpecialEvent : public Event {
public:
    SpecialEvent(const string& name) : Event(name){}

    string getDescription() const override{ return eventName; }


};

class SolarEclips : public SpecialEvent {
public:
    SolarEclips() : SpecialEvent("SolarEclipse") {}

    string playTurn(Player& player) override;

};


class PotionsMerchant : public SpecialEvent {
public:
    PotionsMerchant() : SpecialEvent("PotionsMerchant") {}

    string playTurn(Player& player) override;

};
