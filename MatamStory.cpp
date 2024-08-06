#include "MatamStory.h"
#include "Utilities.h"
#include "Events/EventFactory.h"
#include "Players/PlayerFactory.h"
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;
#include <cctype>


using std::string;
using std::shared_ptr;
using std::vector;
using std::queue;

bool checkValidation(const string& s){
    for(char c : s){
        char lower = tolower(c);
        if(!isalpha(lower)){
            return false;
        }
    }
    return true;
}

std::vector<string> splitString(const string& str) {
    std::vector<string> tokens;
    istringstream iss(str);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


bool comparePlayers(const shared_ptr<Player>& player1, const shared_ptr<Player>& player2) {
    // Compare by level
    if (player1->getLevel() != player2->getLevel()) {
        return player1->getLevel() > player2->getLevel(); // Higher level comes first
    }

    // Compare by number of coins
    if (player1->getCoins() != player2->getCoins()) {
        return player1->getCoins() > player2->getCoins(); // More coins come first
    }

    // Compare by name lexicographically
    return player1->getName() < player2->getName(); // Lexicographically smaller name comes first
}



void getPack(const std::vector<string>& result, std::vector<string>& toadd, size_t& index) {
    if (index >= result.size()) {
        throw InvalidEvents();
    }

    if (result[index] != "Pack") {
        throw InvalidEvents();
    }

    size_t quantityIndex = index + 1;
    if (quantityIndex >= result.size()) {
        throw InvalidEvents();
    }

    int quantity = stoi(result[quantityIndex]);
    if (quantity <= 0) {
        throw InvalidEvents();
    }

    toadd.push_back(result[index]); // Push "Gang"
    toadd.push_back(result[quantityIndex]); // Push quantity

    size_t startIndex = index + 2;
    index = startIndex;

    while (quantity > 0) {
        if (index >= result.size()) {
            throw InvalidEvents();
        }

        if (result[index] == "Pack") {
            getPack(result, toadd, index); // Recursively handle nested "Gang" entries
        } else {
            if(result[index]=="Barlog" ||result[index]=="Slime" || result[index]=="Snail"){
                toadd.push_back(result[index]); // Push individual cards
                index++;
            }
            else{
                throw InvalidEvents();
            }

        }
        quantity--;
    }
}

void MatamStory::getEvents(std::istream& eventsStream){
   /* ifstream file(Eventspath);
    if(!file.is_open()){
        //need to do somthing
        return;
    }*/
    std::vector<std::string> result;
    string line;
    while (getline(eventsStream, line)) {
        std::vector<std::string> tokens = splitString(line);
        result.insert(result.end(), tokens.begin(), tokens.end());
    }
    if(result.empty()){
        throw InvalidEvents();
    }
    EventFactory factory;
    std::vector<string> toadd;
    for(size_t i = 0 ; i < result.size() ; i++){
        if(result[i] == "Gang"){
            getPack(result,toadd,i);
            try {
                m_events.push_back(factory.createEvent(toadd));
                i--;
                toadd.clear();
            }
            catch(const InvalidEvents& e){
                // cout<<"error\n";
                throw e;
            }

        }
        else{
            toadd = {result[i]};
            try{
                m_events.push_back(factory.createEvent(toadd));
                toadd.clear();
            }
            catch(const InvalidEvents& e){
                // cout<<"error\n";
                throw e;
            }
        }
    }
    if(m_events.size() < 2){
        throw InvalidEvents();
    }
}
void MatamStory::getPlayers(std::istream& playersStream){
  /*  ifstream file(playersPath);
    if(!file.is_open()){
        return;
    }*/
    std::vector<std::string> result;
    string line;
    PlayerFactory factory;
    while (getline(playersStream, line)) {
        std::vector<std::string> tokens = splitString(line);
        if(tokens.size() == 3){
            if(!checkValidation(tokens[0])){
                throw InvalidPlayers();
            }
            m_players.push_back(factory.createPlayer(tokens[0],tokens[1],tokens[2]));
        }
        else{
            throw InvalidPlayers();
        }
        // result.insert(result.end(), tokens.begin(), tokens.end());
    }
    if(m_players.size() > 6 || m_players.size()  < 2){
        throw InvalidPlayers();
    }


}
MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
    getEvents(eventsStream);
    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/
    getPlayers(playersStream);
    /*============================================*/


    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    shared_ptr<Event> curEvent = m_events[m_turnIndex % m_events.size()];
    printTurnDetails(m_turnIndex, player, *curEvent);
    //Playing the Event:
    string outcomeMessage = (*curEvent).playTurn(player);
    printTurnOutcome(outcomeMessage);

    m_turnIndex++;
}



void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for(int i = 0; i < m_players.size(); ++i) {
        if(m_players[i]->getHealthPoints() > 0) {
            playTurn(*m_players[i]);
        }
    }
    /*=============================================*/

    sort(m_players.begin(),m_players.end(),comparePlayers);
    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    for(int i = 0; i < m_players.size(); ++i) {
        printLeaderBoardEntry(i + 1, *m_players[i]); //WRONG!!! it should be according to levels
    }
    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    for(int i = 0; i < m_players.size(); ++i) {
        if(m_players[i]->getLevel() == 10) {
            return true;
        }
        if(m_players[i]->getHealthPoints() != 0) {
            return false;
        }
    }
    return true; // all health points are 0
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    for(int i = 0; i < m_players.size(); ++i) {
        printStartPlayerEntry(i + 1, *m_players[i]);
    }
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/


    /*========================================================================*/
}
