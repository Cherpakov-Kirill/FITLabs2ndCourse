#include "optimalPlayer.h"

ship *optimalPlayer::checkTheShipAndSetHit(pair<uint,uint> coordinates) {
    return checkTheShip(coordinates);
}

char optimalPlayer::getSymbolInMapVector(uint xPos, uint yPos){
    pair<uint,uint> coordinatesOnMap = getCoordinatesOnMapVector(make_pair(xPos,yPos));
    if(xPos>MAPSIZE||xPos<=0) return '\0';
    if(yPos>MAPSIZE||yPos<=0) return '\0';
    return mapVectorEnemy[coordinatesOnMap.first][coordinatesOnMap.second];
}

pair<uint,uint> optimalPlayer::getCoordinatesForStep() {
    uint squareOfMap = MAPSIZE*MAPSIZE;
    bool correctNewPosition = false;
    pair<uint,uint> newCoordinates;
    if(lastSuccessStep){
        if(destroyedCoordinatesOnLastStep.size()==1){
            uint xPos = destroyedCoordinatesOnLastStep.begin()->first;
            uint yPos = destroyedCoordinatesOnLastStep.begin()->second;
            if(getSymbolInMapVector(xPos-1,yPos)==' '){
                correctNewPosition = true;
                newCoordinates=make_pair(xPos-1,yPos);
            }
            else if(getSymbolInMapVector(xPos,yPos-1)==' '){
                correctNewPosition = true;
                newCoordinates=make_pair(xPos,yPos-1);
            }
            else if(getSymbolInMapVector(xPos+1,yPos)==' '){
                correctNewPosition = true;
                newCoordinates=make_pair(xPos+1,yPos);
            }
            else if(getSymbolInMapVector(xPos,yPos+1)==' '){
                correctNewPosition = true;
                newCoordinates=make_pair(xPos,yPos+1);
            }
            else {
                cout<<"Something went wrong! (get coordinates in optimal player)\n";
                exit(0);
            }
        }
        else{
            sort(destroyedCoordinatesOnLastStep.begin(),destroyedCoordinatesOnLastStep.end(),comparatorForVectorCoordinates);
            while(!correctNewPosition){
                pair<uint,uint> start = *destroyedCoordinatesOnLastStep.begin();
                pair<uint,uint> finish = destroyedCoordinatesOnLastStep.back();
                if(start.first==finish.first){
                    if(getSymbolInMapVector(start.first,start.second-1)==' '){
                        correctNewPosition = true;
                        newCoordinates=make_pair(start.first,start.second-1);
                    }
                    else if(getSymbolInMapVector(finish.first,finish.second+1)==' '){
                        correctNewPosition = true;
                        newCoordinates=make_pair(finish.first,finish.second+1);
                    }
                    else {
                        cout<<"Something went wrong! (get coordinates in optimal player)\n";
                        exit(0);
                    }
                }
                else{
                    if(getSymbolInMapVector(start.first-1,start.second)==' '){
                        correctNewPosition = true;
                        newCoordinates=make_pair(start.first-1,start.second);
                    }
                    else if(getSymbolInMapVector(finish.first+1,finish.second)==' '){
                        correctNewPosition = true;
                        newCoordinates=make_pair(finish.first+1,finish.second);
                    }
                    else {
                        cout<<"Something went wrong! (get coordinates in optimal player)\n";
                        exit(0);
                    }
                }
            }
        }
    }
    else{
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
    }
    shots++;
    return newCoordinates;
}

bool optimalPlayer::stepOfPlayer(player *currentPlayer, player *enemyPlayer){
    ///for(int i=0;i<ENTERS;i++) cout<<endl;
    ///printGameJudge();
    pair<uint,uint> coordinatesOfHit = getCoordinatesForStep();
    //cout<<coordinatesOfHit.first<<" "<<coordinatesOfHit.second<<endl;
    ship *enemyShip = enemyPlayer->checkTheShipAndSetHit(coordinatesOfHit);
    while(enemyShip != nullptr){
        lastSuccessStep=true;
        destroyedCoordinatesOnLastStep.emplace_back(coordinatesOfHit);
        setHitOnEnemyMap(coordinatesOfHit);
        if(enemyShip->destroyed){
            lastSuccessStep = false;
            destroyedCoordinatesOnLastStep.clear();
            setEnvironmentOfEnemyShipOnMap(enemyShip->destroyedCoordinates);
            ///printGameJudge();
            if(currentPlayer->checkWin()){
                cout<<name<<" have just won the round! Congratulations! :)\n";
                cout<<name<<"'s statistics:\n";
                printStatistics();
                return true;
            }
        }
        //else printGameJudge();
        coordinatesOfHit = getCoordinatesForStep();
        enemyShip = enemyPlayer->checkTheShipAndSetHit(coordinatesOfHit);
    }
    setMissOnEnemyMap(coordinatesOfHit);
    //printGameJudge();
    //sleep(2);
    return false;
}

void optimalPlayer::createShips() {
    cout<<name<<"'s game map\n";
    autoGeneratorOfMap();
    //printUserMapInConsole();
}