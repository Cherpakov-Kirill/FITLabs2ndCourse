#ifndef LAB3_RANDOMPLAYER_H
#define LAB3_RANDOMPLAYER_H
#include "player.h"

class randomPlayer: public player, public Map{
public:
    string name;
    explicit randomPlayer(string &playerName):Map(){
        name = playerName;
    }
    ship *checkTheShipAndSetHit(pair<uint,uint> coordinates) override;
    pair<uint,uint> getCoordinatesForStep();
    bool stepOfPlayer(player *currentPlayer, player *enemyPlayer) override;
    void createShips() override;
};


#endif //LAB3_RANDOMPLAYER_H
