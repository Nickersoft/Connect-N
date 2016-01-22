#include "node.h"

Node::Node() {
	this->board = NULL;
	this->player = NULL;
	this->maximizingPlayer = NULL;
	this->parent = NULL;
}

Node::Node(Board *b, Player *p, Player *maximizingPlayer, int depthLimit) {
	this->board = b;
	this->player = p;
	this->maximizingPlayer = maximizingPlayer;
	this->parent = NULL;
	this->depthLimit = depthLimit;
}

Node::Node(Board *b, Player *p, Node *parent) {
	this->board = b;
	this->player = p;
	this->maximizingPlayer = parent->maximizingPlayer;
	this->parent = parent;
	this->depthLimit = parent->depthLimit;
}

Node::Node(const Node &obj) {
	this->board = obj.board;
	this->maximizingPlayer = obj.maximizingPlayer;
	this->player = obj.player;
	this->parent = obj.parent;
	this->depthLimit = obj.depthLimit;
}

void Node::addNode(Node* n) {
    this->nodes.push_back(n);
}

void Node::clearNodes() {
	this->nodes.clear();
}

void Node::setNodes(vector<Node*> nodes) {
    this->nodes = nodes;
}

vector<Node*> Node::getNodes() {
	return this->nodes;
}

int Node::count() {
    return this->nodes.size();
}

void Node::generateNodes(int depth) {
	this->clearNodes();

    for(int i = 0; i < this->board->width - 1; i++) {
		Board *b = this->board;
		Player *p;
		Player *max_p = this->maximizingPlayer;

		if (this->player == max_p) {
			p = max_p->getOpponent();
		} else {
			p = this->maximizingPlayer;
		}

        Board *b1 = new Board(*b);
        Board *b2 = new Board(*b);

		b1->makeMove(i, DROP, p);
		b2->makeMove(i, POPOUT, p);

		Node *n1 = new Node(b1, p->getOpponent(), this);
		Node *n2 = new Node(b2, p->getOpponent(), this);

		this->nodes.push_back(n1);
		this->nodes.push_back(n2);
    }
}

int Node::heuristic(Node*) {
	return rand() % 50 + 1;
}

int Node::minimax(int depth) {
	int v, bestValue;
	vector<Node*> subnodes;

	if (depth == 0 || depth == this->depthLimit) {
		return heuristic(this);
	}

	subnodes = this->getNodes();
	bestValue = 0;

	if (this->player == this->maximizingPlayer) {
		for(int i = 0; i < subnodes.size(); i++) {
			Node* child = subnodes.at(i);
			v = minimax(depth - 1);
			bestValue = max(bestValue, v);
		}
	} else {
		for(int i = 0; i < subnodes.size(); i++) {
			Node* child = subnodes.at(i);
			v = minimax(depth - 1);
			bestValue = min(bestValue, v);
		}
	}

	return bestValue;
}


// 01 function minimax(node, depth, maximizingPlayer)
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
// }
