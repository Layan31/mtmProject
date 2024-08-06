#include "EventFactory.h"

#include <memory>
#include "SpecialEvent.h"
#include "Event.h"
#include "Encounter.h"
#include <memory>
#include <vector>

std::shared_ptr<Event> EventFactory::createEvent(const std::vector<string>& line) {

    if(line[0] == "Pack"){
        int amount = stoi(line[1]);
        std::vector<Encounter> pack1;
        for(size_t i = 2; i < line.size() ; i++){
            if(line[i]=="Balrog"){
                pack1.push_back(Balrog());
            }
            else if(line[i] == "Slime"){
                pack1.push_back(Slime());
            }
            else if(line[i] == "Snail"){
                pack1.push_back(Snail());
            }
        }

        return std::make_shared<Pack>(pack1, amount);
    }
    else if(line[0] == "Balrog"){
        return std::make_shared<Balrog>();
    }
    else if(line[0] == "Snail"){
        return std::make_shared<Snail>();
    }
    else if(line[0] == "Slime"){
        return std::make_shared<Slime>();
    }
    else if(line[0] == "SolarEclips"){
        return std::make_shared<SolarEclips>();
    }
    else if(line[0] == "PotionsMerchant"){
        return std::make_shared<PotionsMerchant>();
    }
    else{
        throw InvalidEvents();
    }

}
