#include "player.h"

Player::Player() {
	this->name = "aa";
	this->first_move = false;
}

string Player::getName() {
	return this->name;
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
		case 5: // Received move
			cout << "0 1" << endl; // first move

			int height, width, n;

			height = atoi(vs.at(0).c_str());
			width = atoi(vs.at(1).c_str());
			n = atoi(vs.at(2).c_str());

			this->gpTree = new Node(height, width, n);
			// this->first_move = (vs[3]==)
			this->time_limit = atoi(vs.at(4).c_str());
			// [in this order]: board height (#rows), board width (#columns), number of pieces to win (the N in Connect-N), turn of the player (1 indicating 1st player, and 2 indicating 2nd player(the image below is wrong in that it uses 1 and 0), and the time limit to make a move in seconds. Once the players receive these information, the game starts immediately. These are sent as a one line separated with spaces. Example:
			break;
		case 4: //player1: aa player2: bb
			//TODO combine this information with game information to decide who is the first player
			break;
		default:
			cout << "not what I want" << endl;
			break;
	}
}
