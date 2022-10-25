#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>

#include "Player.h"
#include "PlayingField.h"
//#include "FastGameMod.h"
#include "MoveMatrix.h"
//#include "TournamentGameMod.h"
//#include "DetailedGameMod.h"
#include "Factory.h"
#include "ParsingCommandLineArgs.h"

#include "../strategies/include/SimpleStrategy.h"
#include "../strategies/include/DefaultStrategy.h"
#include "../strategies/include/RandomStrategy.h"


class ParsingCommandLineArgs;
class Game
{
private:
    typedef bool (Game::*MFP)();



    bool isGameStarted_ = false;

    int argc_;
    std::vector<std::string> argv_;
    friend ParsingCommandLineArgs;

    ParsingCommandLineArgs *parsing;

    int numOfPrisoners = 3;
    int numOfMoves_ = 6;

    int currentMove_ = 1;

    std::vector<std::string> strategiesList_ =
            {"simple", "default", "random"
            };

    std::vector<Player> players_;

    PlayingField playingField_;

    std::map<std::string, MFP> commandList_;



    void parseParams();

    void setUpCommands();

    bool setUpGame();

    bool endGame();

    bool continueGame();

public:

    Game(int argc, const char **argv);

    ~Game();

    void run();
};
