#include "node.h"

Node::Node() {}

Node::Node(int width, int height, int n) {
	this->board = new Board(height, width, n);
}

void Node::addNode(Node n) {
    this->nodes.push_back(n);
}

void Node::setNodes(vector<Node> nodes) {
    this->nodes = nodes;
}

int Node::count() {
    return this->nodes.size();
}

void Node::generateNodes() {
    for(int i = 0; i < this->board->getWidth() - 1; i++) {
        Board *board1 = this->board;
        Board *board2 = this->board;
        // if(board1->canDropADiscFromTop(i, )) {
        //
        // }
    }
}

int Node::minimax() {


//     01 function minimax(node, depth, maximizingPlayer)
// 02     if depth = 0 or node is a terminal node
// 03         return the heuristic value of node
//
// 04     if maximizingPlayer
// 05         bestValue := −∞
// 06         for each child of node
// 07             v := minimax(child, depth − 1, FALSE)
// 08             bestValue := max(bestValue, v)
// 09         return bestValue
//
// 10     else    (* minimizing player *)
// 11         bestValue := +∞
// 12         for each child of node
// 13             v := minimax(child, depth − 1, TRUE)
// 14             bestValue := min(bestValue, v)
// 15         return bestValue
}
