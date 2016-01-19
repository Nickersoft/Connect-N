#include "tools.h"
#include <iostream>

using namespace std;

// String splitting based on implementation by patchouli found at
// http://code.runnable.com/VHb0hWMZp-ws1gAr/splitting-a-string-into-a-vector-for-c
vector<string> Tools::split(const string &str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}

void Tools::println() {
    cout << endl;
}

void Tools::println(string t) {
    cout << t << endl;
}
