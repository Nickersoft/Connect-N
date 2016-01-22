#ifndef __NODE_INCLUDED__
#define __NODE_INCLUDED__

#include <algorithm>
#include <string>
#include <vector>

class Player;
class Board;

#include "board.h"
#include "player.h"
#include "tools.h"

using namespace Tools;
using namespace std;

class Node {

private:
    Board           *board;
    int             depthLimit;
    string          name;
    vector<Node*>   nodes;
    Node*           parent;
    Player          *player;
    Player          *maximizingPlayer;

public:
    Node();
    Node(Board*, Player*, Player*, int);
    Node(Board*, Player*, Node*);
    Node(const Node&);

    void            addNode(Node*);
    void            clearNodes();
    int             count();
    void            generateNodes();
    Board*          getBoard();
    vector<Node*>   getNodes();
    int             heuristic(Node*);
    int             minimax(int);
    void            setNodes(vector<Node*>);
};

#endif
