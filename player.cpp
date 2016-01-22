#include "player.h"

Player::Player() {
	srand(time(NULL));
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

void Player::processInput() {

	string input;
	getline(cin, input);

	vector<string> vs = Tools::split(input, ' ');

	switch(vs.size()) {
		case 2: // Play
			cout << vs.at(0) + " " + vs.at(1) << endl;
			break;
		case 1:
			cout << "game over!!!" << endl;
			break;
		case 5: // Received game info
			int height, width, n, first_turn;
			Board *b;

			height 		= atoi(vs.at(0).c_str());
			width 		= atoi(vs.at(1).c_str());
			n 			= atoi(vs.at(2).c_str());
			first_turn 	= atoi(vs.at(3).c_str());

			b = new Board(height, width, n);
			b->makeMove(0, 1, this);

			this->first_move = (first_turn == this->number);
			this->time_limit = atoi(vs.at(4).c_str());

			if (this->opponent != NULL) {
				this->gpTree = new Node(b, this, this, MAXDEPTH);
				gpTree->generateNodes();
			}

			println("0 1");

			break;
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

			this->opponent = new Player(opponent_name, opponent_number);
			this->opponent->setOpponent(this);

			break;
		}
		default:
			cout << "not what I want" << endl;
			break;
	}

}
