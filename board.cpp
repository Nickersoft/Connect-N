#include "board.h"

/*********************
   PRIVATE FUNCTIONS
**********************/

int Board::get(int x, int y) {
	return layout.at(x).at(y);
}

void Board::set(int row, int col, int new_value) {
	layout.at(row).at(col) = new_value;
}

bool Board::canRemoveADiscFromBottom(int col, int currentPlayer) {
	if (col < 0 || col >= width) {
		error("Illegal column!");
		return false;
	}
	else if (get(height - 1, col) != currentPlayer) {
		error("You don't have a checker in column %d to pop out!\n", col);
		return false;
	}
	else {
		return true;
	}
}

bool Board::canDropADiscFromTop(int col, int currentPlayer) {
	if(col < 0 || col >= width) {
		error("Illegal column!");
		return false;
	}
	else if(numOfDiscsInColumn.at(col) == height) {
		error("Column is already full. Cannot drop more disc in it.");
		return false;
	}
	else {
		return true;
	}
}

/**
  * Check if one of the players gets N checkers in a row (horizontally, vertically or diagonally)
  * @return the value of winner. If winner=-1, nobody win and game continues; If winner=0/TIE, it's a tie;
  * If winner=1, player1 wins; If winner=2, player2 wins.
*/

map<int, int> Board::checkDiagonally1(int playerNumber) {
	//check diagonally y = -x+k
	int max = 0;
	int upper_bound = height - 1 + width - 1 - (N - 1);

	map<int, int> returnMap;

	for (int i = 1; i <= N; i++) {
		returnMap[i] = 0;
	}

	for(int k = N - 1; k <= upper_bound; k++) {
		max = 0;
		int x, y;
		if (k < width)
			x = k;
		else
			x = width-1;
		y = -x+k;

		while (x >= 0  && y < height) {
			if (get(height - 1 - y, x) == playerNumber) {
				max++;
			}
			else {
				if (max > 0 && max <= N) {
					returnMap[max]++;
				}
				max = 0;
			}
			x--;
			y++;
		}
	}

	return returnMap;
}

map<int, int> Board::checkDiagonally2(int playerNumber) {
	//check diagonally y = x-k
	int max = 0;
	int upper_bound = width - 1 - (N - 1);
	int lower_bound = -(height - 1 - (N - 1));

	map<int, int> returnMap;

	for (int i = 1; i <= N; i++) {
		returnMap[i] = 0;
	}

	for(int k = lower_bound; k <= upper_bound; k++) {
		max = 0;
		int x, y;
		if(k >= 0)
			x = k;
		else
			x = 0;
		y = x-k;
		while(x >= 0 && x < width && y < height) {
			if(get(height - 1 - y, x) == playerNumber) {
				max++;
			}
			else {
				if (max > 0 && max <= N) {
					returnMap[max]++;
				}
				max = 0;
			}
			x++;
			y++;
		}

	}	 //end for y = x-k

	return returnMap;
}

map<int, int> Board::checkHorizontally(int playerNumber) {
	int max = 0;
	map<int, int> returnMap;

	for (int i = 1; i <= N; i++) {
		returnMap[i] = 0;
	}

	//check each row, horizontally
	for(int i = 0; i < this->height; i++) {
		max = 0;
		for(int j = 0;j < this->width; j++) {
			if(get(i, j) == playerNumber) {
				max++;
			}
			else {
				if (max > 0 && max <= N) {
					returnMap[max]++;
				}
				max = 0;
			}
		}
	}

	return returnMap;
}

map<int, int> Board::checkVertically(int playerNumber){
	//check each column, vertically
	int max = 0;
	map<int, int> returnMap;

	for (int i = 1; i <= N; i++) {
		returnMap[i] = 0;
	}

	for(int j=0; j < this->width; j++) {
		max = 0;
		for(int i = 0; i < this->height; i++) {
			if(get(i, j) == playerNumber) {
				max++;
			}
			else {
				if (max > 0 && max <= N) {
					returnMap[max]++;
				}
				max = 0;
			}
		}
	}

	return returnMap;
}

void Board::dropADiscFromTop(int col, int currentplayer) {
	int firstEmptyCellRow = height - numOfDiscsInColumn.at(col) - 1;
	set(firstEmptyCellRow, col, currentplayer);
	numOfDiscsInColumn.at(col) += 1;
}

void Board::removeADiscFromBottom(int col) {
	int i;
	for(i = height - 1; i > height - numOfDiscsInColumn.at(col); i--) {
		set(i, col, get(i-1, col));
	}
	set(i, col, emptyCell);
	numOfDiscsInColumn.at(col) -= 1;
}

vector< vector<int> > Board::resize_layout(vector< vector<int> > layout, int new_height, int new_width) {
    layout.resize(new_height);
    for (int i = 0; i < new_height; ++i)
        layout[i].resize(new_width);
    return layout;
}

void Board::setBoard(int row, int col, int player) {
	if(row >= height || col >= width)
		error("The row or column number is out of bound!");
	if(player != PLAYER1 && player != PLAYER2)
		error("Wrong player!");
	set(row, col, player);
}

/********************
   PUBLIC FUNCTIONS
*********************/

Board::Board(const Board &obj) {
    this->width = obj.width;
    this->height = obj.height;
    this->N = obj.N;
    this->layout = obj.layout;
    this->numOfDiscsInColumn = obj.numOfDiscsInColumn;
    this->popOutCount = obj.popOutCount;
}

Board::Board(int height, int width, int N) {
	this->width  = width;
	this->height = height;
	this->N = N;
    this->layout = resize_layout(layout, height, width);

    this->popOutCount.resize(2);
    this->popOutCount[0] = 0;
    this->popOutCount[1] = 0;

	for(int i = 0; i < height; i++) {
		for(int j=0; j < width; j++){
			set(i, j, emptyCell);
		}
    }

	numOfDiscsInColumn.resize(width);
}

Move Board::getLastPlayed() {
	return this->lastPlayedMove;
}

bool Board::makeMove(Move m, Player *p) {
	if (m.operation == DROP) {
        if (this->canDropADiscFromTop(m.column, m.operation)) {
			this->dropADiscFromTop(m.column, p->getNumber());
			this->lastPlayedMove = m;
            return true;
		}
        else
            return false;
    }
	else if (m.operation== POPOUT) {
        if ((this->canRemoveADiscFromBottom(m.column, p->getNumber())
            && (popOutCount[p->getNumber() - 1] == 0))) {
				this->removeADiscFromBottom(m.column);
				popOutCount[p->getNumber() - 1] += 1;
				this->lastPlayedMove = m;
				return true;
			}
    	else
        	return false;
    }
    else {
        error("Wrong operation.");
        return false;
    }
}

int Board::getHeight() {
	return this->height;
}

map<int, int> Board::getPlays(int playerNumber) {
	map<int, int> returnMap;
	map<int, int> player_h  = this->checkHorizontally(playerNumber);
	map<int, int> player_v  = this->checkVertically(playerNumber);
	map<int, int> player_d1 = this->checkDiagonally1(playerNumber);
	map<int, int> player_d2 = this->checkDiagonally2(playerNumber);
	for(int i = 1; i <= N; i++) {
		returnMap[i] = player_h[i] + player_v[i] + player_d1[i] + player_d2[i];
	}
	return returnMap;
}

int Board::getWidth() {
	return this->width;
}

int Board::getN() {
	return this->N;
}

void Board::printBoard() {
	println("Board: ");
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			printf("%d ", get(i, j));
		}
		println();
	}
}

void Board::printBoard(bool debug) {
	string printString = "";
	if (debug) {
		printString = "\nBoard: \n";
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				char buffer[2];
				snprintf(buffer, sizeof(buffer), "%d ", get(i, j));
				printString += buffer;
				printString += " ";
			}
			printString += "\n";
		}
		log(printString);
	} else {
		this->printBoard();
	}
}

int Board::isConnectN() {
	println("called");
	int player1_horizontal 	= checkHorizontally(PLAYER1)[N];
	int player1_vertical 	= checkVertically(PLAYER1)[N];
	int player1_diagonal1 	= checkDiagonally1(PLAYER1)[N];
	int player1_diagonal2 	= checkDiagonally2(PLAYER1)[N];

	int player2_horizontal 	= checkHorizontally(PLAYER2)[N];
	int player2_vertical 	= checkVertically(PLAYER2)[N];
	int player2_diagonal1 	= checkDiagonally1(PLAYER2)[N];
	int player2_diagonal2 	= checkDiagonally2(PLAYER2)[N];

	int tmp_winner = NOCONNECTION;

	if(player1_horizontal || player1_vertical || player1_diagonal1 || player1_diagonal2)
		tmp_winner = PLAYER1;
	if (player2_horizontal || player2_vertical || player2_diagonal1 || player2_diagonal2)
		tmp_winner = PLAYER2;

	return tmp_winner;
}

bool Board::isFull() {
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++) {
			if(get(i, j) == emptyCell)
				return false;
		}
	return true;
}

/**
 * test is connect N diagonally y=-x+k
 * */
void Board::test1() {
	 dropADiscFromTop(2, 1);
	 dropADiscFromTop(1, 2);
	 dropADiscFromTop(1, 1);
	 dropADiscFromTop(0, 2);
	 dropADiscFromTop(0, 1);
	 dropADiscFromTop(2, 2);
	 dropADiscFromTop(0, 1);
	 printBoard(true);
	 int tmp_winner= isConnectN();
	 log("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=-x+k
* */
void Board::test2(){
	setBoard(1, 2, PLAYER1);
	setBoard(2, 3, PLAYER1);
	setBoard(3, 4, PLAYER1);
	printBoard(true);
	int tmp_winner = isConnectN();
	log("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=x-k
* */
void Board::test3(){
	setBoard(5, 4, PLAYER1);
	setBoard(4, 5, PLAYER1);
	setBoard(3, 6, PLAYER1);
	printBoard(true);
	int tmp_winner= isConnectN();
	log("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=-x+k
* */
void Board::test4(){
	setBoard(2, 0, PLAYER1);
	setBoard(3, 1, PLAYER1);
	setBoard(5, 3, PLAYER1);
	printBoard(true);
	int tmp_winner= isConnectN();
	log("Winner: %d\n", tmp_winner);
}

/**
* test should ends with tie
* */
void Board::test5(){
	setBoard(2, 0, PLAYER1);
	setBoard(3, 1, PLAYER1);
	setBoard(4, 2, PLAYER1);
	setBoard(0, 3, PLAYER2);
	setBoard(2, 5, PLAYER2);
	setBoard(2, 3, PLAYER2);
	setBoard(1, 4, PLAYER2);
	printBoard(true);
	int tmp_winner= this->isConnectN();
	log("Winner: %d\n", tmp_winner);
}
