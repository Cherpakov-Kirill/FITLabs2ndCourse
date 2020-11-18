#ifndef MAIN_CPP_INTERACTIVEPLAYER_H
#define MAIN_CPP_INTERACTIVEPLAYER_H
#include "player.h"

class interactivePlayer: public player, public Map {
    string name;
    bool lastEnemyStepWasSuccess;
    bool lastEnemyStepDestroyedTheShip;
    pair<uint,uint> lastCoordinatesOfSuccessEnemyStep;
public:
    explicit interactivePlayer(string &playerName):Map(){
        name = playerName;
        lastEnemyStepWasSuccess = false;
        lastEnemyStepDestroyedTheShip = false;
    }
    ship *checkTheShipAndSetHit(pair<uint,uint> coordinates) override;
    pair<uint,uint> getCoordinatesForStep();
    bool stepOfPlayer(player *currentPlayer, player *enemyPlayer) override;
    void createShips() override;
};

#endif //MAIN_CPP_INTERACTIVEPLAYER_H
