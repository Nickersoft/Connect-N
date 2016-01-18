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
		case 2:
			cout << vs.at(0) + " " + vs.at(1) << endl;
			break;
		case 1:
			cout << "game over!!!" << endl;
			break;
		case 5:
			cout << "0 1" << endl; // first move
			break;
		case 4: //player1: aa player2: bb
			//TODO combine this information with game information to decide who is the first player
			break;
		default:
			cout << "not what I want" << endl;
			break;
	}
}
