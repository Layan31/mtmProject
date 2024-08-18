#pragma once
#include <string>

class Job {
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

protected:
    bool closeEncounter = false;
    bool isMagical = false;

};

class Magician : public Job {
public:
    Magician() {
        isMagical = true;
    }

    virtual ~Magician() = default;

    std::string getJobName() const override {
        return "Magician";
    }
};

class Archer : public Job {
public:
    virtual ~Archer() = default;


    std::string getJobName() const override {
        return "Archer";
    }
};

class Warrior : public Job {
public:
    Warrior() {
        closeEncounter = true;
    }

    virtual ~Warrior() = default;


    std::string getJobName() const override {
        return "Warrior";
    }
};
