#ifndef __PLAYER_INCLUDED__
#define __PLAYER_INCLUDED__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

struct Move;
class Board;

#include "tools.h"
#include "board.h"

using namespace std;

typedef struct {
    Board* board;
    int value;
} HeuristicNode;

class Player {
private:
    Board*  board;
    bool    first_move;
    string  name;
    int     number;
    Player* opponent;
    int     time_limit;

    HeuristicNode   minimax(Board*, int, int, int, Player*, Player*);
    int             calc_heuristic(Board*);

public:
    Player();
    Player(string, int);

    bool    getFirstMove();
    Move    getMove();
    string  getName();
    int     getNumber();
    Player* getOpponent();
    void    processInput();
    void    setFirstMove(bool);
    void    setOpponent(Player*);
};

#endif
