#include "randomPlayer.h"

ship *randomPlayer::checkTheShipAndSetHit(pair<uint,uint> coordinates) {
    return checkTheShip(coordinates);
}

pair<uint,uint> randomPlayer::getCoordinatesForStep() {
    uint squareOfMap = MAPSIZE*MAPSIZE;
    bool correctNewPosition = false;
    pair<uint,uint> newCoordinates;
    while(!correctNewPosition){
        uint randomValue = randomize(squareOfMap);
        uint xPos = randomValue%10 == 0 ? 10 : randomValue%10;
        uint yPos = randomValue%10 == 0 ? randomValue/10 : randomValue/10+1;
        pair<uint,uint> coordinatesOnMap = getCoordinatesOnMapVector(make_pair(xPos,yPos));
        if(mapVectorEnemy[coordinatesOnMap.first][coordinatesOnMap.second]==' '){
            correctNewPosition = true;
            newCoordinates=make_pair(xPos,yPos);
        }
    }
    shots++;
    return newCoordinates;
}

bool randomPlayer::stepOfPlayer(player *currentPlayer, player *enemyPlayer){
    //for(int i=0;i<ENTERS;i++) cout<<endl;
    //printGameJudge();
    pair<uint,uint> coordinatesOfHit = getCoordinatesForStep();
    ship *enemyShip = enemyPlayer->checkTheShipAndSetHit(coordinatesOfHit);
    while(enemyShip != nullptr){
        setHitOnEnemyMap(coordinatesOfHit);
        if(enemyShip->destroyed){
            setEnvironmentOfEnemyShipOnMap(enemyShip->destroyedCoordinates);
            //printGameJudge();
            if(currentPlayer->checkWin()){
                cout<<name<<" have just won the round! Congratulations! :)\n";
                cout<<name<<"'s statistics:\n";
                printStatistics();
                return true;
            }
        }
        coordinatesOfHit = getCoordinatesForStep();
        enemyShip = enemyPlayer->checkTheShipAndSetHit(coordinatesOfHit);
        //else printGameJudge();
    }
    setMissOnEnemyMap(coordinatesOfHit);
    //printGameJudge();
    //sleep(1);
    return false;
}

void randomPlayer::createShips() {
    cout<<name<<"'s game map\n";
    autoGeneratorOfMap();
    //printUserMapInConsole();
}