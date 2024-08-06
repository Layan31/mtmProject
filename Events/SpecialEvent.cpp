#include "SpecialEvent.h"
#include "../Players/Player.h"



string PotionsMerchant::playTurn(Player& player1) {
    int amount = (player1.getCharacter())->playTurnWithPM(player1);
    return getPotionsPurchaseMessage(player1, amount);
}

string SolarEclips::playTurn(Player& player) {
    if(player.getJob()->getIsMagical()) {
        player.setForce(player.getForce() + 1);
        return getSolarEclipseMessage(player, 1);
    } else {
        player.setForce(player.getForce() - 1);
        return getSolarEclipseMessage(player, -1);
    }
}