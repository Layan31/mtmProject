#include "MatamStory.h"
#include "Utilities.h"
#include "Events/EventFactory.h"
#include "Players/PlayerFactory.h"
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <fstream>
using std::string;
using std::shared_ptr;
using std::vector;
using std::queue;

bool checkValidation(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        char currentChar = str[i];
        char lowerChar = char(std::tolower(currentChar));

        if (!std::isalpha(lowerChar)) {
            return false;
        }
    }
    return true;
}


#include <vector>
#include <string>

std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char ch : str) {
        // Check for whitespace characters manually
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f' || ch == '\v') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken += ch;
        }
    }

    // Add the last token if there is one
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}


bool comparePlayers(const std::shared_ptr<Player>& p1, const std::shared_ptr<Player>& p2) {
    // Compare levels first
    int level1 = p1->getLevel();
    int level2 = p2->getLevel();
    if (level1 != level2) {
        return level1 > level2; // Higher level first
    }

    // Compare coins next
    int coins1 = p1->getCoins();
    int coins2 = p2->getCoins();
    if (coins1 != coins2) {
        return coins1 > coins2; // More coins first
    }

    // Finally, compare names lexicographically
    const std::string& name1 = p1->getName();
    const std::string& name2 = p2->getName();
    return name1 < name2; // Lexicographically smaller name first
}



void getPack(const std::vector<std::string>& source, std::vector<std::string>& destination,
             size_t& currentIndex) {
    // Check if the index is out of bounds
    if (currentIndex >= source.size()) {
        throw InvalidEvents();
    }

    // Check if the current element is "Pack"
    std::string firstElement = source[currentIndex];
    if (firstElement != "Pack") {
        throw InvalidEvents();
    }

    size_t quantityIdx = currentIndex + 1;
    if (quantityIdx >= source.size()) {
        throw InvalidEvents();
    }

    // Get the quantity and validate it
    int packQuantity = std::stoi(source[quantityIdx]);
    if (packQuantity <= 0) {
        throw InvalidEvents();
    }

    // Add "Pack" and its quantity to the destination vector
    destination.push_back(firstElement);
    destination.push_back(source[quantityIdx]);

    currentIndex = quantityIdx + 1; // Move past "Pack" and quantity

    while (packQuantity > 0) {
        if (currentIndex >= source.size()) {
            throw InvalidEvents();
        }

        std::string currentElement = source[currentIndex];
        if (currentElement == "Pack") {
            getPack(source, destination, currentIndex);
        } else if (currentElement == "Balrog" || currentElement == "Slime" ||
            currentElement == "Snail") {
            destination.push_back(currentElement); // Add the event to the destination
            ++currentIndex;
        } else {
            throw InvalidEvents();
        }
        --packQuantity; // Decrement the remaining number of events in this pack
    }
}

void MatamStory::getEvents(std::istream& eventsStream) {
    std::vector<std::string> result;
    std::string line;

    // Read all lines from the stream and split into tokens
    while (std::getline(eventsStream, line)) {
        std::vector<std::string> tokens = splitString(line);
        result.insert(result.end(), tokens.begin(), tokens.end());
    }

    if (result.empty()) {
        throw InvalidEvents();
    }

    EventFactory factory;
    std::vector<std::string> temp;
    size_t index = 0;

    while (index < result.size()) {
        if (result[index] == "Pack") {
            // Handle the Pack event
            getPack(result, temp, index);
            try {
                eventsSet.push_back(factory.createEvent(temp));
                temp.clear();
            } catch (const InvalidEvents&) {
                throw;
            }
        } else {
            temp.assign(1, result[index]);
            try {
                eventsSet.push_back(factory.createEvent(temp));
                temp.clear();
            } catch (const InvalidEvents&) {
                throw;
            }
            ++index; // Move to the next item after processing the current event
        }
    }

    if (eventsSet.size() < 2) {
        throw InvalidEvents();
    }
}

void MatamStory::getPlayers(std::istream& playersStream) {
    std::vector<std::string> tokens;
    std::string line;
    PlayerFactory factory;

    // Read the entire stream line by line and concatenate all lines into a single string
    while (std::getline(playersStream, line)) {
        std::vector<std::string> lineTokens = splitString(line);
        tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
    }

    // Check if the number of tokens is a multiple of 3
    if (tokens.size() % 3 != 0) {
        throw InvalidPlayers();
    }

    for (size_t i = 0; i < tokens.size(); i += 3) {
        bool isValid = checkValidation(tokens[i]);
        if (!isValid) {
            throw InvalidPlayers();
        }

        // Create player using a temporary shared_ptr
        std::shared_ptr<Player> tempPlayer = factory.createPlayer(tokens[i],
            tokens[i+1], tokens[i+2]);
        playersSet.push_back(tempPlayer);
        playersSortedSet.push_back(tempPlayer);
    }

    size_t playerCount = playersSet.size();
    if (playerCount > 6 || playerCount < 2) {
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
    shared_ptr<Event> curEvent = eventsSet[m_turnIndex % eventsSet.size()];
    printTurnDetails(m_turnIndex + 1, player, *curEvent);
    //Playing the Event:
    string outcomeMessage = (*curEvent).playTurn(player);
    printTurnOutcome(outcomeMessage);

    m_turnIndex++;
}



void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for(int i = 0; i < (int)playersSet.size(); ++i) {
        if(playersSet[i]->getHealthPoints() > 0) {
            playTurn(*playersSet[i]);
        }
    }
    /*=============================================*/

    sort(playersSortedSet.begin(),playersSortedSet.end(),comparePlayers);
    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    for(int i = 0; i < (int)playersSortedSet.size(); ++i) {
        printLeaderBoardEntry(i + 1, *playersSortedSet[i]);
    }
    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    for(int i = 0; i < (int)playersSet.size(); ++i) {
        if(playersSet[i]->getLevel() == 10) {
            return true;
        }
        if(playersSet[i]->getHealthPoints() != 0) {
            return false;
        }
    }
    return true; // all health points are 0
    /*===================================================*/
}

void MatamStory::play() {
    m_turnIndex = 0;
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    for(int i = 0; i < (int)playersSet.size(); ++i) {
        printStartPlayerEntry(i + 1, *playersSet[i]);
    }
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    for(int i = 0; i < (int)playersSortedSet.size(); ++i) {
        if(playersSortedSet[i]->getLevel() == 10) {
            printWinner(*playersSortedSet[i]);
            return;
        }
    }
    printNoWinners();

    /*========================================================================*/
}