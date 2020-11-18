#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "optionparser.h"
#include "baseOfGame.h"

using namespace std;

struct Arg: public option::Arg{
    static void printError(const char* msg1, const option::Option& opt, const char* msg2){
        fprintf(stderr, "%s", msg1);
        fwrite(opt.name, opt.namelen, 1, stderr);
        fprintf(stderr, "%s", msg2);
    }
    static option::ArgStatus Unknown(const option::Option& option, bool msg){
        if (msg) printError("Unknown option '", option, "'\n");
        return option::ARG_ILLEGAL;
    }
    static option::ArgStatus Numeric(const option::Option& option, bool msg){
        char* endptr = 0;
        if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
        if (endptr != option.arg && *endptr == 0)
            return option::ARG_OK;

        if (msg) printError("Option '", option, "' requires a numeric argument\n");
        return option::ARG_ILLEGAL;
    }
};

enum  optionIndex { UNKNOWN, HELP, FIRST, SECOND, COUNT };

const option::Descriptor usage[] ={
        {UNKNOWN, 0,"" , ""    ,Arg::Unknown, "USAGE: example [options]\n\n" "Options:" },
        {HELP,    0,"" , "help",Arg::None, "  --help\tArguments for First and Second: Interactive, Random, Optimal." },
        {FIRST,    0,"f", "first",Arg::Optional, "  --first, -f  \tYou can type in console --first={argument}. \nDefault parameter is Random." },
        {SECOND, 0,"s" ,  "second"   ,Arg::Optional, "  --second, -s  \tYou can type in console --second={argument}. \nDefault parameter is Random." },
        {COUNT, 0,"c" ,  "count"   ,Arg::Numeric, "  --count, -c  \tYou can type number of rounds --count={number}. \nDefault parameter is 1." },
        {0,0,0,0,0,0}
};

void setPlayersModes(int numberOfPlayer, PlayerMode type, PlayerMode &firstPlayerMode, PlayerMode &secondPlayerMode){
    switch (numberOfPlayer) {
        case FIRST:
            firstPlayerMode = type;
            break;
        case SECOND:
            secondPlayerMode = type;
            break;
    }
}

int main(int argc, char *argv[]) {
    argc-=(argc>0);
    argv+=(argc>0); // skip program name argv[0] if present
    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error()) return 1;

    if(options[UNKNOWN]) return 0;

    if(parse.nonOptionsCount() > 0){
        for(int i = 0; i < parse.nonOptionsCount(); ++i)
            fprintf(stdout, "Unknown argument #%d is %s\n", i, parse.nonOption(i));
        return 0;
    }

    if (options[HELP]){
        int columns = getenv("COLUMNS")? atoi(getenv("COLUMNS")) : 80;
        option::printUsage(fwrite, stdout, usage, columns);
        return 0;
    }

    ///set-up default parameters
    int numberOfRounds = 1;
    PlayerMode firstPlayerMode = PlayerMode::RANDOM;
    PlayerMode secondPlayerMode = PlayerMode::RANDOM;


    ///set-up users parameters
    for(int numberOfPlayer=FIRST;numberOfPlayer<=SECOND;numberOfPlayer++){
        if(options[numberOfPlayer]){
            if(options[numberOfPlayer].arg == ((string)"Random")) setPlayersModes(numberOfPlayer,RANDOM, firstPlayerMode,secondPlayerMode);
            else if(options[numberOfPlayer].arg == ((string)"Optimal")) setPlayersModes(numberOfPlayer,OPTIMAL, firstPlayerMode,secondPlayerMode);
            else if (options[numberOfPlayer].arg == ((string)"Interactive"))  setPlayersModes(numberOfPlayer,INTERACTIVE, firstPlayerMode,secondPlayerMode);
            else {
                cout<<"Error with unknown mode of player: "<<options[numberOfPlayer].arg<<" :/";
                return 0;
            }
        }
    }
    ///number of rounds in game
    if(options[COUNT]){
        numberOfRounds = atoi(options[COUNT].arg);
        if(numberOfRounds <= 0){
            cout<<"Error with number of rounds in the game: "<<numberOfRounds<<" :/";
            return 0;
        }
    }
    ///start the game
    playTheGame(numberOfRounds,firstPlayerMode,secondPlayerMode);
    return 0;
}
