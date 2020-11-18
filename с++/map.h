#ifndef MAIN_CPP_MAP_H
#define MAIN_CPP_MAP_H

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <unistd.h>
#include <vector>

typedef unsigned int uint;

using namespace std;

#define ENTERS 30
#define SPACES_BETWEEN_MAPS 10
#define MAPSIZE 10
#define HOWMUCHSHIPS 10
enum oppositePlayers{
    CURRENT,
    ENEMY
};

enum class shipsType: int {
    //numbers of deck on the current ship
    FOURDECK = 4,
    THREEDECK = 3,
    TWODECK = 2,
    ONEDECK = 1,
    UNSETED = 0
};

typedef struct ship{
    ship(shipsType type, vector<pair<uint,uint>> vectorCoordinates){
        shipType = type;
        coordinates = move(vectorCoordinates);
        length = (uint)type;
        health = (uint)type;
    }
    shipsType shipType = shipsType::UNSETED;
    uint length = 0;
    vector<pair<uint,uint>> coordinates;
    bool destroyed = false;
    vector<pair<uint,uint>> destroyedCoordinates;
    uint health = 0;
} ship;

class Map {
protected:
    vector <ship> allShipsVector;  ///0 - FourDeck, 1,2 - ThreeDeck, 3,4,5 - TwoDeck, 6,7,8,9 - OneDeck

    uint misses = 0; ///промахи user
    uint hits = 0; ///попадания user
    uint shots = 0; ///выстрелы user

    ///horizontal orientation is x vector; vertical is y vector

    vector<vector<char>> mapVectorUser;
    vector<vector<char>> mapVectorEnemy;

    map <pair<uint,uint>, uint> coordinatorMapUser;
    set <pair<uint,uint>> coordinatorMapEnemy;

    static bool comparatorForVectorCoordinates(pair<uint,uint> firstPair, pair<uint,uint> secondPair);

    uint randomize(uint interval);

    void printUserMapInConsole();
    void printGameJudge();
    void printStatistics();

    static pair<uint, uint> getCoordinatesOnMapVector(pair<uint, uint> pairOfCoordinates);
    static uint retOfPointerOfShipInVector(shipsType type, uint numberOfShip); //Returns pointer of vector in allShipsVector
    static uint retOfNumberOfCurrentShip(shipsType type); //How much the ships in current Type?

    bool checkIntervalOnMapUser(pair<uint,uint> FirstPair, pair<uint,uint> LastPair);

    void setSymbolInEnemyEnvironment(uint xPos, uint yPos);
    void setEnvironmentOfEnemyShipOnMap(vector<pair<uint, uint>> coordinatesOfShip);
    void setMissOnEnemyMap(pair<uint,uint> coordinates);
    void setHitOnEnemyMap(pair<uint,uint> coordinates);
    ship *checkTheShip(pair<uint,uint> coordinates);

    void setShipOnMapVector(pair<uint, uint> coordinates, uint pointerOfShipInVector);
    void putCoordinatesOfTheShip(pair<uint,uint> FirstPair,pair<uint,uint> LastPair, shipsType type, uint numberOfShip);
    pair<pair<uint,uint>,pair<uint,uint>> findNewPositionForCurrentShip(uint squareOfMap, int numberOfDecks);
    void autoGeneratorOfMap();

    vector <vector<char>> makeMapInVector();
    Map();


};
#endif //MAIN_CPP_MAP_H
