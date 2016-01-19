#ifndef __PLAYER_INCLUDED__
#define __PLAYER_INCLUDED__

#define BUFFER_SIZE 10

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "tools.h"
#include "node.h"

using namespace std;

class Player {
    bool    first_move;
    int     time_limit;
    Node    *gpTree;
    string  name;

public:
    Player();

    string getName();

    void processInput();
};

#endif
