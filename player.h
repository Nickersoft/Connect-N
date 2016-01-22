#ifndef __PLAYER_INCLUDED__
#define __PLAYER_INCLUDED__

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Node;

#include "tools.h"
#include "node.h"

using namespace std;

class Player {
private:
    bool    first_move;
    Node*   gpTree;
    string  name;
    int     number;
    Player* opponent;
    int     time_limit;


public:
    Player();
    Player(string, int);

    bool    getFirstMove();
    string  getName();
    int     getNumber();
    Player* getOpponent();
    void    processInput();
    void    setFirstMove(bool);
    void    setOpponent(Player*);
};

#endif
