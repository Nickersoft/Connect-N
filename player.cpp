#include "player.h"

/***************
  CONSTRUCTORS
****************/

/*
 * Name: Player()
 * Type: constructor
 * Description: Initializes player with dummy values
 * Parameters: None
 * Returns: Player
 */
Player::Player() {
	srand(time(NULL) ^ (getpid() << 16));
	this->name = "player" + Tools::itos(rand() % (9999-5555) + 5555);
	this->number = -1;
	this->first_move = false;
	this->opponent = NULL;
}

/*
 * Name: Player(string, int)
 * Type: constructor
 * Description: Initializes player using a name and number
 * Parameters:
 * 	- name: the name to assign to the player
 *	- number: the number to assign to the player
 * Returns: Player
 */
Player::Player(string name, int number) {
	this->name = name;
	this->number = number;
	this->opponent = NULL;
}

/**********
  GETTERS
***********/

/*
 * Name: getFirstMove()
 * Type: constructor
 * Description: Returns a value denoting whether the current player makes the first move
 * Parameters: None
 * Returns: Boolean
 */
bool Player::getFirstMove() {
	return this->first_move;
}

/*
 * Name: getName()
 * Type: getter
 * Description: Return the name of the current player
 * Parameters: None
 * Returns: String
 */
string Player::getName() {
	return this->name;
}

/*
 * Name: getNumber()
 * Type: getter
 * Description: Return the number of the current player
 * Parameters: None
 * Returns: String
 */
int Player::getNumber() {
	return this->number;
}

/*
 * Name: Player()
 * Type: getter
 * Description: Return the opponent of the current player as a separate Player object
 * Parameters: None
 * Returns: Player*
 */
Player* Player::getOpponent() {
	return this->opponent;
}

/**********
  SETTERS
***********/

/*
 * Name: setFirstMove(bool)
 * Type: setter
 * Description: Sets whether the current player has the first move
 * Parameters:
 * 	- first_move: A boolean representing whether the current player has the first move
 * Returns: None
 */
void Player::setFirstMove(bool first_move) {
	this->first_move = first_move;
}

/*
 * Name: setOpponent(Player*)
 * Type: setter
 * Description: Sets the opponent player of the current player
 * Parameters:
 * 	- o: A player object representing the opponent of the current player
 * Returns: None
 */
void Player::setOpponent(Player* o) {
	this->opponent = o;
}

/***********************
  MINIMAX & HEURISTICS
************************/

/*
 * Name: calcHeuristic(Board*)
 * Type: private method
 * Description: Analyzes a given board and computes a heuristic based on its current state
 * Parameters:
 * 	- b: The board to analyze
 * Returns: Integer representing the calculated heuristic
 */
int Player::calcHeuristic(Board* b) {
	int h;
	float constant;
	bool all_single_plays;
	map<int, int> myPlays, opponentPlays;

	myPlays = b->getPlays(this->getNumber());
	opponentPlays = b->getPlays(this->getOpponent()->getNumber());

	h = 0;
	all_single_plays = true;
	constant = 100 / b->getN();

	if (DEBUG) {
		log("");
		log("------------");
		b->printBoard(true);
	}

	// Make move based on how many checkers you have matched, minus the opponent's checkers
	for(int a = 1; a <= b->getN(); a++) {
		if (DEBUG)
			log(itos(a) + ": " + itos(myPlays[a]) + ", " + itos(opponentPlays[a]));

		if (a > 1)
			all_single_plays = !(myPlays[a] > 0 || opponentPlays[a] > 0);

		h +=  (constant*a)*pow(myPlays[a], a) - (constant*a)*pow(opponentPlays[a], a);
	}

	// If we can either win the game or block the opponent,
	// weigh this the most heavily
	if ((myPlays[b->getN()] > 0) ||
		(myPlays[1] > opponentPlays[1] && all_single_plays)) {
		h = numeric_limits<int>::max();
	}

	// If the opponent wins, weigh this the least heavily
	if (opponentPlays[b->getN()] > 0)
		h = numeric_limits<int>::min();

	if (DEBUG) {
		log("");
		log("Computed heuristic: " + itos(h) + " for move " + itos(b->getLastPlayed().column) + " " + itos(b->getLastPlayed().operation));
	}

	return h;
}

/*
 * Name: minimax(Board*, int, int, int, Player*, Player*)
 * Type: private method
 * Description: Creates and traverses a minimax tree to calculate the next play
 * Parameters:
 * 	- board: The board at the current node
 * 	- depth: The current depth of the tree, working backwards (i.e. depth = 0 is the bottom of the tree)
 *	- a: The current alpha value
 * 	- b: The current beta value
 *	- player: The "current" player for this iteration (min or max)
 * 	- maximizingPlayer: The maximizingPlayer (the original player playing the game)
 * 	- isChild: Denotes whether the current recursion is performed on a child of board node
 * Returns: HeuristicNode containing a board and a heuristic value
 */
HeuristicNode Player::minimax(Board* board, int depth, int a, int b, Player* player, Player* maximizingPlayer, bool isChild) {
	HeuristicNode returnNode;
	vector<Board*> children;

	// Set the return node to the last played move
	returnNode.move = board->getLastPlayed();

    if (depth == 0) {
		returnNode.value = calcHeuristic(board);
		return returnNode;
	}

	if (DEBUG) {
		log("");
		log("************");
		log("   DEPTH " + itos(depth));
		log("************");
	}

	// Generate the children of the current node
	for(int i = 0; i < board->getWidth(); i++) {
		Board *b1, *b2;

		Move m1 = {i, DROP};
		Move m2 = {i, POPOUT};

        b1 = new Board(*(board));
        b2 = new Board(*(board));

		if (b1->makeMove(m1, player)) {
			children.push_back(b1);
		}

		if (b2->makeMove(m2, player))
			children.push_back(b2);
    }

	// If we're the maximizing player...
    if (player->getNumber() == maximizingPlayer->getNumber()) {
		returnNode.value = numeric_limits<int>::min();
		// Recurse on the children and find the maximum value
		for(int i = 0; i < (int)children.size(); i++) {
			Board* child = children.at(i);
			HeuristicNode recurseMinimax = minimax(child, depth - 1, a, b, player->getOpponent(), maximizingPlayer, true);

			if (recurseMinimax.value > returnNode.value) {
				returnNode.value = recurseMinimax.value;
				if (!isChild) {
					returnNode.move = recurseMinimax.move;
				}
			}

			a = max(a, returnNode.value);

			if (b <= a) // Alpha-beta pruning
				break;
		}
	// If we're the minimizing player...
    } else {
		returnNode.value = numeric_limits<int>::max();
		// Recurse on the children and find the minimum value
		for(int i = 0; i <(int)children.size(); i++) {
			Board* child = children.at(i);
			HeuristicNode recurseMinimax = minimax(child, depth - 1, a, b, player->getOpponent(), maximizingPlayer, true);

			if (recurseMinimax.value < returnNode.value) {
				returnNode.value = recurseMinimax.value;
			}

			b = min(b, returnNode.value);

			if (b <= a)  // Alpha-beta pruning
				break;
		}
	}

	return returnNode;
}

/*
 * Name: getMove()
 * Type: public method
 * Description: Gets the next moving using the minimax algorithm
 * Parameters: None
 * Returns: Move containing a column and an operation
 */
Move Player::getMove() {
	int neg_inf, pos_inf;

	neg_inf = numeric_limits<int>::min();
	pos_inf = numeric_limits<int>::max();

	HeuristicNode node = minimax(this->board, MAXDEPTH, neg_inf, pos_inf, this, this, false);
	Move m = node.move;

	if (DEBUG) {
		log("============");
		log("Chose board with heuristic " + itos(node.value));
	}

	return m;
}

/********
  OTHER
*********/

/*
 * Name: processInput()
 * Type: public method
 * Description: Processes input sent by referee
 * Parameters: None
 * Returns: None
 */
void Player::processInput() {

	string input;
	getline(cin, input);

	vector<string> vs = Tools::split(input, ' '); // Get the input and split it by spaces

	switch(vs.size()) {
		case 2: // Opponent move received
			Move curMove, nextMove;

			curMove.column = atoi(vs.at(0).c_str());
			curMove.operation = atoi(vs.at(1).c_str());

			this->board->makeMove(curMove, this->getOpponent());
			nextMove = this->getMove();
			this->board->makeMove(nextMove, this);

			cout << itos(nextMove.column) + " " + itos(nextMove.operation) << endl;

			if (DEBUG)
				log(this->getName() + " played move " + itos(nextMove.column) + " " + itos(nextMove.operation));

			break;
		case 1: // Game over
			cout << "game over!!!" << endl;
			break;
		case 5: {  // Received initial game info
			int height, width, n, first_turn;

			height 		= atoi(vs.at(0).c_str());
			width 		= atoi(vs.at(1).c_str());
			n 			= atoi(vs.at(2).c_str());
			first_turn 	= atoi(vs.at(3).c_str());

			Move m = {Tools::rand_from_range(0, width - 1), DROP};

			this->board = new Board(height, width, n);

			this->first_move = (first_turn == this->number);
			this->time_limit = atoi(vs.at(4).c_str());

			// Make first move if chosen to do so
			if (first_move) {
				this->board->makeMove(m, this);
				println(itos(m.column) + " " + itos(m.operation));
				if (DEBUG)
					this->board->printBoard(true);
			}

			break;
		}
		case 4: { // Received player names
			string player1_name, player2_name, opponent_name;
			int opponent_number;

			player1_name = vs.at(1);
			player2_name = vs.at(3);

			// If the name matches player 1's name, I'm player 1 and my opponent is player 2
			if (this->name == player1_name) {
				this->number = 1;
				opponent_number = 2;
				opponent_name = player2_name;
			// If not, I'm player 2 and my opponent is player 1
			} else {
				this->number = 2;
				opponent_number = 1;
				opponent_name = player1_name;
			}

			// Set the opponent
			this->setOpponent(new Player(opponent_name, opponent_number));
			this->opponent->setOpponent(this);

			break;
		}
		default: // "I don't know what to do with this input"
			cout << "not what I want" << endl;
			break;
	}

}
