#ifndef __TOOLS_INCLUDED__
#define __TOOLS_INCLUDED__

#define emptyCell 9
#define MAXDEPTH 2
#define PLAYER1 1
#define PLAYER2 2
#define NOCONNECTION -1
#define TIE 0
#define DROP 1
#define POPOUT 0

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

namespace Tools {

    void            error(string);
    void            error(string, int);
    string          itos(int);
    void            log(string);
    void            println();
    void            println(string);
    vector<string>  split(const string&, char);
};

#endif
