#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H
#include "map.h"

enum PlayerMode{ INTERACTIVE, RANDOM, OPTIMAL };

class player {
public:
    uint score = 0;
    bool win = false;
    bool checkWin();
    virtual void createShips() = 0;
    virtual bool stepOfPlayer(player *currentPlayer, player *enemyPlayer) = 0;
    virtual ship *checkTheShipAndSetHit(pair<uint,uint> coordinates) = 0;

    static player *createNewPlayer(PlayerMode playerMode, string &playerName);
};


#endif //LAB3_PLAYER_H
