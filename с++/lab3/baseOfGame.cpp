#include "baseOfGame.h"

string getEndForNumbers(int number){
    switch (number) {
        case 1: return "-st ";
        case 2: return "-nd ";
        case 3: return "-rd ";
        default: return "-th ";
    }
}

void printTheWinner(uint firstScore, uint secondScore, string &nameFirst, string &nameSecond){
    if(firstScore>secondScore) cout<<nameFirst<<" is the winner!\nCongratulations :)\n";
    if(secondScore>firstScore) cout<<nameSecond<<" is the winner!\nCongratulations :)\n";
    if(firstScore==secondScore) cout<<"DRAW.\nPLay again to chose the winner!\n";
}

uint playTheRound(PlayerMode firstPlayerMode, PlayerMode secondPlayerMode, string &nameFirst, string &nameSecond){
    player *firstPlayer = player::createNewPlayer(firstPlayerMode, nameFirst);
    player *secondPlayer = player::createNewPlayer(secondPlayerMode, nameSecond);
    firstPlayer->createShips();
    secondPlayer->createShips();
    bool firstPlayerWon = false, secondPlayerWon = false;
    while(true){
        firstPlayerWon = firstPlayer->stepOfPlayer(firstPlayer,secondPlayer);
        if(firstPlayerWon) break;
        secondPlayerWon = secondPlayer->stepOfPlayer(secondPlayer,firstPlayer);
        if(secondPlayerWon) break;
    }
    if(firstPlayerWon) return 1;
    else return 2;
}

string getName(PlayerMode playerMode, const string& numberOfPlayer){
    string name;
    switch (playerMode) {
        case INTERACTIVE:
            cout<<numberOfPlayer<<" player! Please, type your name.\n";
            cin>>name;
            break;
        case RANDOM:
            name = "Random computer (";
            name+=numberOfPlayer;
            name+=")";
            break;
        case OPTIMAL:
            name = "Optimal computer (";
            name+=numberOfPlayer;
            name+=")";
    }
    return name;
}

void playTheGame(int numberOfRounds, PlayerMode firstPlayerMode, PlayerMode secondPlayerMode){
    string nameFirst = getName(firstPlayerMode,"First");
    string nameSecond = getName(secondPlayerMode,"Second");
    uint firstScore = 0, secondScore = 0;
    for(int i = 1;i<=numberOfRounds;i++){
        cout<<"Round "<<i<<"/"<<numberOfRounds<<endl;
        switch (playTheRound(firstPlayerMode, secondPlayerMode, nameFirst, nameSecond)) {
            case 1:
                firstScore++;
                break;
            case 2:
                secondScore++;
                break;
            default:
                cout<<"Something went wrong. (play the round)\n";
                return;
        }
        cout<<nameFirst<<" has "<<firstScore<<" points!\n";
        cout<<nameSecond<<" has "<<secondScore<<" points!\n";
        cout<<"End of "<<i<<getEndForNumbers(i)<<" round.\n";
    }
    cout<<"End the game!\n";
    printTheWinner(firstScore,secondScore,nameFirst,nameSecond);
    sleep(10);
    cout<<"Press ENTER to exit\n";
    getchar();
    getchar();
}
