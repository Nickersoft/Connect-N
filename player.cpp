#include "player.h"

Player::Player() {
	srand(time(NULL) ^ (getpid() << 16));
	this->name = "player" + Tools::itos(rand() % (9999-5555) + 5555);
	this->number = -1;
	this->first_move = false;
	this->opponent = NULL;
}

Player::Player(string name, int number) {
	this->name = name;
	this->number = number;
	this->opponent = NULL;
}

string Player::getName() {
	return this->name;
}

int Player::getNumber() {
	return this->number;
}

Player* Player::getOpponent() {
	return this->opponent;
}

bool Player::getFirstMove() {
	return this->first_move;
}

void Player::setFirstMove(bool first_move) {
	this->first_move = first_move;
}

void Player::setOpponent(Player* o) {
	this->opponent = o;
}

int Player::calc_heuristic(Board* b) {
	int h;
	map<int, int> myPlays = b->getPlays(this->getOpponent()->getNumber());
	map<int, int> opponentPlays = b->getPlays(this->getOpponent()->getNumber());

	h = 0;

	for(int a = 1; a <= b->getN(); a++) {
		h += (pow(myPlays[a], a) - pow(opponentPlays[a], a));
	}

	return h;
}

HeuristicNode Player::minimax(Board* board, int depth, int a, int b, Player* player, Player* maximizingPlayer) {
	HeuristicNode returnNode;

    if (depth == 0) {
		returnNode.board = board;
		returnNode.value = calc_heuristic(board);
		return returnNode;
	}

	vector<Board*> children;

	for(int i = 0; i < board->getWidth(); i++) {
		Board *b1, *b2;

		Move m1 = {i, DROP};
		Move m2 = {i, POPOUT};

        b1 = new Board(*(board));
        b2 = new Board(*(board));

		if (b1->makeMove(m1, player)) {
			children.push_back(b1);
		}

		if (b2->makeMove(m2, player)) {
			// log("can play move " + itos(m2.column) + " " + itos(m2.operation));
			// b2->printBoard(true);
			children.push_back(b2);
		}
    }

    if (player->getNumber() == maximizingPlayer->getNumber()) {
		returnNode.value = numeric_limits<int>::min();
		for(int i = 0; i < children.size(); i++) {
			Board* child = children.at(i);
			HeuristicNode recurseMinimax = minimax(child, depth - 1, a, b, player->getOpponent(), maximizingPlayer);
			returnNode.board = child;
			if (recurseMinimax.value > returnNode.value)
				returnNode = recurseMinimax;
			a = max(a, returnNode.value);
			if (b <= a)
				break;
		}
    } else {
		returnNode.value = numeric_limits<int>::max();
		for(int i = 0; i < children.size(); i++) {
			Board* child = children.at(i);
			HeuristicNode recurseMinimax = minimax(child, depth - 1, a, b, player->getOpponent(), maximizingPlayer);
			returnNode.board = child;
			if (recurseMinimax.value < returnNode.value)
				returnNode = recurseMinimax;
			b = min(b, returnNode.value);
			if (b <= a)
				break;
		}
	}

	return returnNode;
}

Move Player::getMove() {
	int neg_inf, pos_inf;

	neg_inf = numeric_limits<int>::min();
	pos_inf = numeric_limits<int>::max();

	HeuristicNode node = minimax(this->board, MAXDEPTH, neg_inf, pos_inf, this, this);

	Move m = node.board->getLastPlayed();

	return m;
}

void Player::processInput() {

	string input;
	getline(cin, input);

	vector<string> vs = Tools::split(input, ' ');

	switch(vs.size()) {
		case 2: // Play
			Move curMove, nextMove;

			curMove.column = atoi(vs.at(0).c_str());
			curMove.operation = atoi(vs.at(1).c_str());

			this->board->makeMove(curMove, this->getOpponent());
			nextMove = this->getMove();
			this->board->makeMove(nextMove, this);

			cout << itos(nextMove.column) + " " + itos(nextMove.operation) << endl;
			this->board->printBoard(true);

			log(this->getName() + " played move " + itos(nextMove.column) + " " + itos(nextMove.operation));
			break;
		case 1:
			cout << "game over!!!" << endl;
			break;
		case 5: {  // Received game info
			int height, width, n, first_turn;

			height 		= atoi(vs.at(0).c_str());
			width 		= atoi(vs.at(1).c_str());
			n 			= atoi(vs.at(2).c_str());
			first_turn 	= atoi(vs.at(3).c_str());

			Move m = {Tools::rand_from_range(0, width - 1), DROP};

			this->board = new Board(height, width, n);

			this->first_move = (first_turn == this->number);
			this->time_limit = atoi(vs.at(4).c_str());

			if (first_move) {
				this->board->makeMove(m, this);
				this->board->printBoard(true);
				println(itos(m.column) + " " + itos(m.operation));
			}

			break;
		}
		case 4: { //player1: aa player2: bb
			string player1_name, player2_name, opponent_name;
			int opponent_number;

			player1_name = vs.at(1);
			player2_name = vs.at(3);

			if (this->name == player1_name) {
				this->number = 1;
				opponent_number = 2;
				opponent_name = player2_name;
			} else {
				this->number = 2;
				opponent_number = 1;
				opponent_name = player1_name;
			}

			this->setOpponent(new Player(opponent_name, opponent_number));
			this->opponent->setOpponent(this);

			break;
		}
		default:
			cout << "not what I want" << endl;
			break;
	}

}
