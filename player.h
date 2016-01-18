#ifndef __PLAYER_INCLUDED__
#define __PLAYER_INCLUDED__

#define BUFFER_SIZE 10

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "tools.h"

using namespace std;

class Player {
    string name;
	bool first_move;

public:
    Player();

    string getName();

    void processInput();
};

#endif
