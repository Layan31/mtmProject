#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

#include "Players/Player.h"
#include "Events/Event.h"

class Player;

class MatamStory{
public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

    void getEvents(std::istream& eventsStream);
    void getPlayers(std::istream& playersStream);


private:
    unsigned int m_turnIndex;
    std::deque<std::shared_ptr<Event>> eventsSet;
    std::vector<std::shared_ptr<Player>> playersSet;
    std::vector<std::shared_ptr<Player>> playersSortedSet;

  /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

 /**
  * Plays a single round of the game
  *
  * @return - void
 */
    void playRound();

 /**
  * Checks if the game is over
  *
  * @return - true if the game is over, false otherwise
 */
    bool isGameOver() const;


};
