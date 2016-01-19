#ifndef __TOOLS_INCLUDED__
#define __TOOLS_INCLUDED__

#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace Tools {
    vector<string> split(const string&, char);

    void println();
    void println(string);
};

#endif
