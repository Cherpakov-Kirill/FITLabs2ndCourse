#include "map.h"

vector<vector<char>> Map::makeMapInVector() {
    int xSize = 5+4*MAPSIZE+1;
    int ySize = 2*MAPSIZE +2;
    vector<vector<char>> v(xSize, vector<char> (ySize, 32));
    int positionOnString = 7;
    //1st
    for(int i=1;i<=MAPSIZE;i++){
        if(i>=10&&i<100){
            v[positionOnString][0]=i%10+'0';
            v[positionOnString-1][0]=i/10+'0';
        }
        else if(i>=100&&i<1000){
            v[positionOnString+1][0]=i%10+'0';
            v[positionOnString][0]=i%100/10+'0';
            v[positionOnString-1][0]=i/100+'0';
        } else v[positionOnString][0]=i+'0';
        positionOnString+=4;
    }
    //numberString%2 == 0  in vector 1, 3, 5, 7
    for(int j=1;j<ySize;j+=2){
        for(int i=5;i<xSize;i++){
            v[i][j] = '-';
        }
    }
    //numberString%2 == 1  in vector 2, 4, 6, 8
    //int numerationY = 1;
    int numerationY = 0;
    for(int j=2;j<ySize;j+=2){
        positionOnString = 3;
        v[positionOnString][j]=numerationY+'A';
        /*if(numerationY>=10&&numerationY<100){
            v[positionOnString][j]=numerationY%10+'0';
            v[positionOnString-1][j]=numerationY/10+'0';
        }
        else if(numerationY>=100&&numerationY<1000){
            v[positionOnString][j]=numerationY%10+'0';
            v[positionOnString-1][j]=numerationY%100/10+'0';
            v[positionOnString-2][j]=numerationY/100+'0';
        } else v[positionOnString][j]=numerationY+'0';*/

        for(int i=5;i<xSize;i+=4){
            v[i][j] = '|';
        }
        numerationY++;
    }
    return v;
}

Map::Map() {
    srand(time(0)); // автоматическая рандомизация
    mapVectorUser=makeMapInVector();
    mapVectorEnemy=makeMapInVector();

    pair<uint,uint> p = make_pair(0, 0);
    uint pointerInVector = 0;
    for(int numberOfDecks = (int)shipsType::FOURDECK;numberOfDecks>=(int)shipsType::ONEDECK;numberOfDecks--){
        for(int i = 0; i<retOfNumberOfCurrentShip((shipsType)numberOfDecks);i++){
            vector<pair<uint,uint>> newVector(numberOfDecks,p);
            ship s((shipsType)numberOfDecks, newVector);
            allShipsVector.push_back(s);
            pointerInVector++;
        }
    }
}

bool Map::comparatorForVectorCoordinates(pair<uint,uint> firstPair, pair<uint,uint> secondPair){
    if(firstPair.first == secondPair.first){
        return firstPair.second < secondPair.second;
    }
    else{
        return firstPair.first < secondPair.first;
    }
}

uint Map::randomize(uint interval) {

    return (1 + rand() % interval);
}


pair<uint, uint> Map::getCoordinatesOnMapVector(pair<uint, uint> pairOfCoordinates) {
    uint x = (pairOfCoordinates.first-1)*4+7;
    uint y = (pairOfCoordinates.second-1)*2+2;
    return make_pair(x,y);
}

uint Map::retOfPointerOfShipInVector(shipsType type, uint numberOfShip) {
    uint pointer = 0;
    for(int i = (int)shipsType::FOURDECK;i>(int)type;i--) pointer+=retOfNumberOfCurrentShip((shipsType)i);
    pointer+=(numberOfShip-1);
    return pointer;
}

uint Map::retOfNumberOfCurrentShip(shipsType type) {
    if(type==shipsType::FOURDECK) return 1;
    else if (type == shipsType::THREEDECK) return 2;
    else if (type == shipsType::TWODECK) return 3;
    else if (type == shipsType::ONEDECK) return 4;
    else return 0;
}

void Map::printUserMapInConsole() {
    int xSize = 5+4*MAPSIZE+1;
    int ySize = 2*MAPSIZE +2;
    for(int y=0;y<ySize;y++){ //y
        for(int x=0;x<xSize;x++) cout<<mapVectorUser[x][y]; //x
        cout<<endl;
    }
}

void Map::printGameJudge() {
    int xSize = 5+4*MAPSIZE+1;
    int ySize = 2*MAPSIZE +2;
    for(int y=0;y<ySize;y++){ //y
        for(int x=0;x<xSize;x++) cout<<mapVectorUser[x][y]; //x
        for(int space = 0;space<SPACES_BETWEEN_MAPS;space++) cout<<" ";
        for(int x=0;x<xSize;x++) cout<<mapVectorEnemy[x][y]; //x
        cout<<endl;
    }
}

void Map::printStatistics() {
    cout<<"Number of shots: "<<shots<<endl;
    cout<<"Number of hits: "<<hits<<endl;
    cout<<"Number of misses: "<<misses<<endl;
    uint counterOfAliveShips = 0;
    for(auto ship : allShipsVector){
        if(!ship.destroyed){
            counterOfAliveShips++;
            counterOfAliveShips++;
            cout<<(uint)ship.shipType<<"-deck ship is still alive :)  ";
            if(ship.health>1) cout<<"It have "<<ship.health<<" healths.\n";
            else cout<<"It have "<<ship.health<<" health.\n";
        }
        else cout<<(uint)ship.shipType<<"-deck ship is not still alive :(\n";
    }
    cout<<"Counter of all alive ships = "<<counterOfAliveShips<<endl;
    cout<<"Winner's judge:\n";
    printGameJudge();
}


void Map::setShipOnMapVector(pair<uint, uint> coordinates, uint pointerOfShipInVector){
    coordinatorMapUser.insert(make_pair(coordinates,pointerOfShipInVector));
    pair<uint, uint> currCoordOnMap = getCoordinatesOnMapVector(coordinates);
    mapVectorUser[currCoordOnMap.first][currCoordOnMap.second] = '#';
}

void Map::putCoordinatesOfTheShip(pair<uint,uint> FirstPair,pair<uint,uint> LastPair, shipsType type, uint numberOfShip){
    uint pointer = retOfPointerOfShipInVector(type,numberOfShip);
    auto it = allShipsVector[pointer].coordinates.begin();
    *it = FirstPair;
    setShipOnMapVector(FirstPair,pointer); ///view
    auto prevIt = it;
    it++;
    if(FirstPair.first == LastPair.first){
        while(it!=allShipsVector[pointer].coordinates.end()){
            *it=*prevIt;
            if(FirstPair.second < LastPair.second) (*it).second++;
            else (*it).second--;
            setShipOnMapVector(*it,pointer);
            prevIt=it;
            it++;
        }
    }
    else{
        while(it!=allShipsVector[pointer].coordinates.end()){
            *it=*prevIt;
            if(FirstPair.first < LastPair.first) (*it).first++;
            else (*it).first--;
            setShipOnMapVector(*it,pointer); ///view
            prevIt=it;
            it++;
        }
    }
    sort(allShipsVector[pointer].coordinates.begin(),allShipsVector[pointer].coordinates.end(),comparatorForVectorCoordinates);
}

pair<pair<uint,uint>,pair<uint,uint>> Map::findNewPositionForCurrentShip(uint squareOfMap, int numberOfDecks){
    bool correctNewPosition = false;
    pair<uint,uint> FirstPairOfNewCoordinates;
    pair<uint,uint> LastPairOfNewCoordinates;
    while(!correctNewPosition) {
        uint randomValue = randomize(squareOfMap);
        uint xPos = randomValue%10 == 0 ? 10 : randomValue%10;
        uint yPos = randomValue%10 == 0 ? randomValue/10 : randomValue/10+1;
        FirstPairOfNewCoordinates = make_pair(xPos,yPos);
        uint randomOrientation = randomize(4);
        switch (randomOrientation) {
            case 1:
                if (checkIntervalOnMapUser(FirstPairOfNewCoordinates, make_pair(xPos + (numberOfDecks - 1), yPos))){
                    LastPairOfNewCoordinates = make_pair(xPos + (numberOfDecks - 1), yPos);
                    correctNewPosition = true;
                }
                break;
            case 2:
                if (checkIntervalOnMapUser(FirstPairOfNewCoordinates, make_pair(xPos - (numberOfDecks - 1), yPos))){
                    LastPairOfNewCoordinates = make_pair(xPos - (numberOfDecks - 1), yPos);
                    correctNewPosition = true;
                }
                break;
            case 3:
                if (checkIntervalOnMapUser(FirstPairOfNewCoordinates, make_pair(xPos, yPos + (numberOfDecks - 1)))){
                    LastPairOfNewCoordinates = make_pair(xPos, yPos + (numberOfDecks - 1));
                    correctNewPosition = true;
                }
                break;
            case 4:
                if (checkIntervalOnMapUser(FirstPairOfNewCoordinates, make_pair(xPos, yPos - (numberOfDecks - 1)))){
                    LastPairOfNewCoordinates = make_pair(xPos, yPos - (numberOfDecks - 1));
                    correctNewPosition = true;
                }
                break;
        }
    }
    return make_pair(FirstPairOfNewCoordinates,LastPairOfNewCoordinates);

}

void Map::autoGeneratorOfMap() {
    uint squareOfMap = MAPSIZE*MAPSIZE;
    for(int numberOfDecks = (int)shipsType::FOURDECK;numberOfDecks>=(int)shipsType::ONEDECK;numberOfDecks--){
        for(int numberOfShip = 1; numberOfShip<=retOfNumberOfCurrentShip((shipsType)numberOfDecks);numberOfShip++){
            pair<pair<uint,uint>,pair<uint,uint>> pairOfPairsOfCoordinatesNewShip = findNewPositionForCurrentShip(squareOfMap, numberOfDecks);
            pair<uint,uint> FirstPair = pairOfPairsOfCoordinatesNewShip.first;
            pair<uint,uint> LastPair = pairOfPairsOfCoordinatesNewShip.second;
            putCoordinatesOfTheShip(FirstPair,LastPair, (shipsType)numberOfDecks, numberOfShip);
        }
    }
}


bool Map::checkIntervalOnMapUser(pair<uint,uint> FirstPair, pair<uint,uint> LastPair){
    if(FirstPair.first>MAPSIZE||FirstPair.first<=0) return false;
    if(FirstPair.second>MAPSIZE||FirstPair.second<=0) return false;
    if(LastPair.first>MAPSIZE||LastPair.first<=0) return false;
    if(LastPair.second>MAPSIZE||LastPair.second<=0) return false;

    if(FirstPair.first == LastPair.first){
        uint xPos = FirstPair.first;
        uint yPosStart = 0;
        uint yPosFinish;
        if(FirstPair.second < LastPair.second){
            yPosStart = FirstPair.second;
            yPosFinish = LastPair.second;
        }
        else{
            yPosStart = LastPair.second;
            yPosFinish = FirstPair.second;
        }
        if(coordinatorMapUser.count(make_pair(xPos,yPosStart-1))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPos+1,yPosStart-1))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPos-1,yPosStart-1))==1) return false;

        if(coordinatorMapUser.count(make_pair(xPos,yPosFinish+1))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPos+1,yPosFinish+1))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPos-1,yPosFinish+1))==1) return false;
        while(yPosStart<=yPosFinish){
            if(coordinatorMapUser.count(make_pair(xPos,yPosStart))==1) return false;
            if(coordinatorMapUser.count(make_pair(xPos-1,yPosStart))==1) return false;
            if(coordinatorMapUser.count(make_pair(xPos+1,yPosStart))==1) return false;
            yPosStart++;
        }

    }
    else{
        uint yPos = FirstPair.second;
        uint xPosStart = 0;
        uint xPosFinish;
        if(FirstPair.first < LastPair.first){
            xPosStart = FirstPair.first;
            xPosFinish = LastPair.first;
        }
        else{
            xPosStart = LastPair.first;
            xPosFinish = FirstPair.first;
        }
        if(coordinatorMapUser.count(make_pair(xPosStart-1,yPos))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPosStart-1,yPos+1))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPosStart-1,yPos-1))==1) return false;

        if(coordinatorMapUser.count(make_pair(xPosFinish+1,yPos))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPosFinish+1,yPos+1))==1) return false;
        if(coordinatorMapUser.count(make_pair(xPosFinish+1,yPos-1))==1) return false;
        while(xPosStart<=xPosFinish){
            if(coordinatorMapUser.count(make_pair(xPosStart,yPos))==1) return false;
            if(coordinatorMapUser.count(make_pair(xPosStart,yPos-1))==1) return false;
            if(coordinatorMapUser.count(make_pair(xPosStart,yPos+1))==1) return false;
            xPosStart++;
        }
    }
    return true;
}

void Map::setSymbolInEnemyEnvironment(uint xPos, uint yPos){
    pair<uint, uint> currCoordOnMap = getCoordinatesOnMapVector(make_pair(xPos,yPos));
    if(xPos<=MAPSIZE && xPos>0 && yPos <=MAPSIZE && yPos>0 && mapVectorEnemy[currCoordOnMap.first][currCoordOnMap.second]==' '){
        mapVectorEnemy[currCoordOnMap.first][currCoordOnMap.second] = '-';
    }
}

void Map::setEnvironmentOfEnemyShipOnMap(vector<pair<uint, uint>> coordinatesOfShip) {
    if(coordinatesOfShip.begin()->first == coordinatesOfShip.back().first){
        auto it = coordinatesOfShip.begin();
        setSymbolInEnemyEnvironment(it->first,it->second-1);
        setSymbolInEnemyEnvironment(it->first-1,it->second-1);
        setSymbolInEnemyEnvironment(it->first+1,it->second-1);

        while(it!=coordinatesOfShip.end()){
            setSymbolInEnemyEnvironment(it->first-1,it->second);
            setSymbolInEnemyEnvironment(it->first+1,it->second);
            it++;
        }
        it--;
        setSymbolInEnemyEnvironment(it->first,it->second+1);
        setSymbolInEnemyEnvironment(it->first-1,it->second+1);
        setSymbolInEnemyEnvironment(it->first+1,it->second+1);
    }
    else{
        auto it = coordinatesOfShip.begin();
        setSymbolInEnemyEnvironment(it->first-1,it->second);
        setSymbolInEnemyEnvironment(it->first-1,it->second-1);
        setSymbolInEnemyEnvironment(it->first-1,it->second+1);

        while(it!=coordinatesOfShip.end()){
            setSymbolInEnemyEnvironment(it->first,it->second-1);
            setSymbolInEnemyEnvironment(it->first,it->second+1);
            it++;
        }
        it--;
        setSymbolInEnemyEnvironment(it->first+1,it->second);
        setSymbolInEnemyEnvironment(it->first+1,it->second-1);
        setSymbolInEnemyEnvironment(it->first+1,it->second+1);
    }
}

void Map::setMissOnEnemyMap(pair<uint, uint> coordinates) {
    pair<uint, uint> currCoordOnMap = getCoordinatesOnMapVector(coordinates);
    mapVectorEnemy[currCoordOnMap.first][currCoordOnMap.second]='*';
    misses++;
}

void Map::setHitOnEnemyMap(pair<uint, uint> coordinates) {
    coordinatorMapEnemy.insert(coordinates);
    hits++;
    pair<uint, uint> currCoordOnMap = getCoordinatesOnMapVector(coordinates);
    mapVectorEnemy[currCoordOnMap.first][currCoordOnMap.second] = '@';
}

ship *Map::checkTheShip(pair<uint, uint> coordinates) {
    pair<uint, uint> currCoordOnMap = getCoordinatesOnMapVector(coordinates);
    if(coordinatorMapUser.count(coordinates)){
        uint numberOfShipInVectorShips = coordinatorMapUser[coordinates];
        allShipsVector[numberOfShipInVectorShips].destroyedCoordinates.emplace_back(coordinates);
        allShipsVector[numberOfShipInVectorShips].health--;
        if(allShipsVector[numberOfShipInVectorShips].health == 0) {
            allShipsVector[numberOfShipInVectorShips].destroyed = true;
            sort(allShipsVector[numberOfShipInVectorShips].destroyedCoordinates.begin(),allShipsVector[numberOfShipInVectorShips].destroyedCoordinates.end(),comparatorForVectorCoordinates);
        }
        mapVectorUser[currCoordOnMap.first][currCoordOnMap.second] = '@';
        return &allShipsVector[numberOfShipInVectorShips];
    }
    mapVectorUser[currCoordOnMap.first][currCoordOnMap.second] = '*';
    return nullptr;

}