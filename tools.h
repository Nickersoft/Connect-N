#ifndef __TOOLS_INCLUDED__
#define __TOOLS_INCLUDED__

#include <cstdarg>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

namespace Tools {

    void            error(string);
    void            error(string, int);
    string          itos(int);
    void            log(string);
    void            log(string, int);
    void            println();
    void            println(string);
    vector<string>  split(const string&, char);
    int             rand_from_range(int, int);
};

#endif
