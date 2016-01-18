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

	cout << vs.size() << endl;

	for (int i = 0; i < vs.size() - 1; i++) {
		cout << vs.at(i) << endl;
	}

	switch(vs.size()) {
		case 2:
			cout << vs.at(0) + " " + vs.at(1);
			break;
		case 1:
			cout << "game over!!!";
			break;
		case 5:
			cout << "0 1"; // first move
			break;
		case 4: //player1: aa player2: bb
			//TODO combine this information with game information to decide who is the first player
			break;
		default:
			cout << "not what I want";
			break;
	}
}
