#ifndef __NODE_INCLUDED__
#define __NODE_INCLUDED__

#include <vector>
#include <string>

#include "tools.h"
#include "board.h"

using namespace std;

class Node {
    Board *board;
    vector<Node> nodes;

public:
    Node();
    Node(int, int, int);

    void    addNode(Node);
    int     count();
    void    generateNodes();
    int     minimax();
    void    setNodes(vector<Node>);
};

#endif
