#include "player.h"
#include "interactivePlayer.h"
#include "optimalPlayer.h"
#include "randomPlayer.h"

player *player::createNewPlayer(PlayerMode playerMode, string &playerName) {
    player *newPlayerType = nullptr;
    switch (playerMode) {
        case INTERACTIVE:
            newPlayerType = new interactivePlayer(playerName);
            break;
        case RANDOM:
            newPlayerType = new randomPlayer(playerName);
            break;
        case OPTIMAL:
            newPlayerType = new optimalPlayer(playerName);
            break;
    }
    return newPlayerType;
}

bool player::checkWin() {
    score++;
    if(score==HOWMUCHSHIPS) return true;
    else return false;
}