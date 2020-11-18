#include "interactivePlayer.h"

void printDescriptionOfCoordinates(){
    cout<<"Please, type coordinates of the ship (only the first and the last position on the map). "
          "\nFor example: \nFirst position: A5 \nLast position: D10 "
          "\nYou needn't type orientation. "
          "Game is able to do all of these operations without any help.\n";
}

void printEntersInConsole(){
    for(int i=0;i<ENTERS;i++) cout<<endl;
}

pair<uint, uint> parseCoordinateStringFromUser(string &input) {
    uint xPos = 0, yPos = 0;
    yPos = (uint)(tolower(input[0])-tolower('A'))+1;
    for(int i=1;i<input.size();i++){
        xPos *=10;
        xPos+=(uint)(input[i]-'0');
    }
    return make_pair(xPos,yPos);
}

pair<uint,uint> readPairOfCoordinates(){
    string input;
    cin>>input;
    pair<uint,uint> coordinatesPair = parseCoordinateStringFromUser(input);
    uint xPos = coordinatesPair.first, yPos = coordinatesPair.second;
    while(xPos>MAPSIZE || yPos>MAPSIZE || xPos<=0 || yPos<=0){
        cout<<"Incorrect input coordinates! Try again! \nNew coordinates: ";
        cin>>input;
        coordinatesPair = parseCoordinateStringFromUser(input);
        xPos = coordinatesPair.first, yPos = coordinatesPair.second;
    }
    return make_pair(xPos,yPos);
}

ship *interactivePlayer::checkTheShipAndSetHit(pair<uint, uint> coordinates) {
    ship *enemyShip = checkTheShip(coordinates);
    if(enemyShip!= nullptr){
        if(enemyShip->destroyed) lastEnemyStepDestroyedTheShip = true;
        lastEnemyStepWasSuccess = true;
        lastCoordinatesOfSuccessEnemyStep = coordinates;
    }
    return enemyShip;
}

pair<uint,uint> interactivePlayer::getCoordinatesForStep(){
    cout<<"What point on the map do you want to beat?\nType coordinates. Character is vertical, number is horizontal.\nExample: A5\nNew coordinates: ";
    string input;
    cin>>input;
    pair<uint,uint> pairOfCoordinates = parseCoordinateStringFromUser(input);
    pair<uint,uint> pairOfCoordinatesOnMapVector = getCoordinatesOnMapVector(pairOfCoordinates);
    while(pairOfCoordinates.first>MAPSIZE || pairOfCoordinates.second>MAPSIZE || pairOfCoordinates.first<=0 || pairOfCoordinates.second<=0 ||
          mapVectorEnemy[pairOfCoordinatesOnMapVector.first][pairOfCoordinatesOnMapVector.second] != ' '){
        cout<<"Incorrect input coordinates! Try again! \nNew coordinates: ";
        cin>>input;
        pairOfCoordinates = parseCoordinateStringFromUser(input);
        pairOfCoordinatesOnMapVector = getCoordinatesOnMapVector(pairOfCoordinates);
    }
    shots++;
    return pairOfCoordinates;
}

bool interactivePlayer::stepOfPlayer(player *currentPlayer, player *enemyPlayer){
    for(int i=0;i<ENTERS;i++) cout<<endl;
    if(lastEnemyStepWasSuccess){
        if(lastEnemyStepDestroyedTheShip) {
            uint numberOfShip = coordinatorMapUser[lastCoordinatesOfSuccessEnemyStep];
            cout<<"Your ship was totally destroyed! Coordinates: ";
            for(auto pairOfCoordinates : allShipsVector[numberOfShip].coordinates) cout<<(char)(pairOfCoordinates.second+'A'-1)<<pairOfCoordinates.first<<" ";
            cout<<endl;
        }
        else cout<<"Your ship was hit! Coordinates: "<<(char)(lastCoordinatesOfSuccessEnemyStep.second+'A'-1)<<lastCoordinatesOfSuccessEnemyStep.first<<endl;
        lastEnemyStepWasSuccess = false;
        lastEnemyStepDestroyedTheShip = false;
    }
    printGameJudge();
    pair<uint,uint> coordinatesOfHit = getCoordinatesForStep();
    ship *enemyShip = enemyPlayer->checkTheShipAndSetHit(coordinatesOfHit);
    while(enemyShip != nullptr){
        cout<<"\nYou hit the ship! GOOD!\n";
        setHitOnEnemyMap(coordinatesOfHit);
        if(enemyShip->destroyed){
            cout<<"You finally destroyed the ship! GOOD!\n";
            setEnvironmentOfEnemyShipOnMap(enemyShip->destroyedCoordinates);
            printGameJudge();
            if(currentPlayer->checkWin()){
                cout<<name<<" have just won the round! Congratulations! :)\n";
                cout<<name<<"'s statistics:\n";
                printStatistics();
                return true;
            }
        }
        else printGameJudge();
        cout<<"Good job!\nYour turn is next. Choose the next position.\n";
        coordinatesOfHit = getCoordinatesForStep();
        enemyShip = enemyPlayer->checkTheShipAndSetHit(coordinatesOfHit);
    }
    cout<<"\nYou missed\n";
    setMissOnEnemyMap(coordinatesOfHit);
    printGameJudge();
    sleep(2);
    return false;
}

void interactivePlayer::createShips(){
    char answer = 0;
    while(tolower(answer, std::locale()) != 'y' && tolower(answer, std::locale()) != 'n'){
        cout << "Would you prefer to place the ships on the field by yourself? (Type: 'y' or 'n', same as Yes or No)\n";
        cin>>answer;
    }
    if(tolower(answer, std::locale()) == 'n'){
        autoGeneratorOfMap();
        cout<<name<<"'s game map\n";
        printUserMapInConsole();
        return;
    }
    else{
        cout<<"Ok, men. You picked the mode setup of positions of all ships by yourself.\n";
        printUserMapInConsole();
        for(int numberOfDecks = (int)shipsType::FOURDECK;numberOfDecks>=(int)shipsType::ONEDECK;numberOfDecks--){
            for(int numberOfShip = 1; numberOfShip<=retOfNumberOfCurrentShip((shipsType)numberOfDecks);numberOfShip++){
                pair<uint,uint> FirstPair;
                pair<uint,uint> LastPair;
                bool checker = false;
                while(!checker){
                    printDescriptionOfCoordinates();
                    cout << "\nType the coordinates of "<<numberOfDecks<<"-DECK ship. \nFirst position: ";
                    FirstPair = readPairOfCoordinates();
                    cout<<"Last  position: ";
                    LastPair = readPairOfCoordinates();

                    uint deltaX = abs((int)FirstPair.first-(int)LastPair.first);
                    uint deltaY = abs((int)FirstPair.second-(int)LastPair.second);
                    if(((deltaX == 0 && deltaY+1 == numberOfDecks) || (deltaX+1 == numberOfDecks && deltaY == 0)) && checkIntervalOnMapUser(FirstPair,LastPair)) checker=true;
                    else cout<<"Sorry! You have written wrong coordinates of the ship! \nTry again.\n\n";
                }
                putCoordinatesOfTheShip(FirstPair,LastPair, (shipsType)numberOfDecks, numberOfShip);
                printEntersInConsole();
                cout<<name<<"'s game map\n";
                printUserMapInConsole();
            }
        }
    }
}