#ifndef LAB3_OPTIMALPLAYER_H
#define LAB3_OPTIMALPLAYER_H
#include "player.h"

class optimalPlayer: public player, public Map {
    bool lastSuccessStep;
    vector <pair<uint,uint>> destroyedCoordinatesOnLastStep;
public:
    string name;
    explicit optimalPlayer(string &playerName):Map(){
        name = playerName;
        lastSuccessStep = false;
    }
    char getSymbolInMapVector(uint xPos, uint yPos);

    ship *checkTheShipAndSetHit(pair<uint,uint> coordinates) override;
    pair<uint,uint> getCoordinatesForStep();
    bool stepOfPlayer(player *currentPlayer, player *enemyPlayer) override;
    void createShips() override;
};


#endif //LAB3_OPTIMALPLAYER_H
