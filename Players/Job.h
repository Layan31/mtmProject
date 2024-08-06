#pragma once
#include <string>

class Job {
protected:
    bool closeEncounter = false;
    bool isMagical = false;

public:
    bool getCloseEncounter() const {
        return closeEncounter;
    }
    bool getIsMagical() const {
        return isMagical;
    }

    Job() = default;
    virtual ~Job() = default;

    virtual std::string getJobName() const = 0;
};

class Magician : public Job {
public:
    Magician() {
        isMagical = true;
    }
    std::string getJobName() const override {
        return "Magician";
    }
};

class Archer : public Job {
public:
    std::string getJobName() const override {
        return "Archer";
    }
};

class Warrior : public Job {
public:
    Warrior() {
        closeEncounter = true;
    }
    std::string getJobName() const override {
        return "Warrior";
    }
};
