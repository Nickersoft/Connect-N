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
	else if (layout[height-1][col] != currentPlayer) {
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

int Board::checkDiagonally1() {
	//check diagonally y = -x+k
	int max1 = 0;
	int max2 = 0;
	bool player1_win = false;
	bool player2_win = false;
	int upper_bound = height - 1 + width - 1 - (N - 1);

	for(int k = N - 1; k <= upper_bound; k++) {
		max1 = 0;
		max2 = 0;
		int x, y;
		if (k < width)
			x = k;
		else
			x = width-1;
		y = -x+k;

		while (x >= 0  && y < height) {
			if (get(height - 1 - y, x) == PLAYER1) {
				max1++;
				max2 = 0;
				if (max1 == N)
					player1_win = true;
			}
			else if (get(height - 1 - y, x) == PLAYER2) {
				max1 = 0;
				max2++;
				if (max2 == N)
					player2_win = true;
			}
			else {
				max1 = 0;
				max2 = 0;
			}
			x--;
			y++;
		}
	}

	if (player1_win && player2_win)
		return TIE;
	if (player1_win)
		return PLAYER1;
	if (player2_win)
		return PLAYER2;

	return NOCONNECTION;
}

int Board::checkDiagonally2() {
	//check diagonally y = x-k
	int max1 = 0;
	int max2 = 0;
	bool player1_win = false;
	bool player2_win = false;
	int upper_bound = width - 1 - (N - 1);
	int lower_bound = -(height - 1 - (N - 1));
	for(int k = lower_bound; k <= upper_bound; k++) {
		max1 = 0;
		max2 = 0;
		int x, y;
		if(k >= 0)
			x = k;
		else
			x = 0;
		y = x-k;
		while(x >= 0 && x < width && y < height) {
			if(get(height - 1 - y, x) == PLAYER1) {
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(get(height - 1 - y, x) == PLAYER2) {
				max1 = 0;
				max2++;
				if(max2 == N)
					player2_win = true;
			}
			else {
				max1 = 0;
				max2 = 0;
			}
			x++;
			y++;
		}

	}	 //end for y = x-k

	if (player1_win && player2_win)
		return TIE;
	if (player1_win)
		return PLAYER1;
	if (player2_win)
	return PLAYER2;

	return NOCONNECTION;
}

int Board::checkHorizontally() {
	int max1 = 0;
	int max2 = 0;
	bool player1_win = false;
	bool player2_win = false;

	//check each row, horizontally
	for(int i = 0; i < this->height; i++) {
		max1 = 0;
		max2 = 0;
		for(int j = 0;j < this->width; j++) {
			if(get(i, j) == PLAYER1){
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(get(i, j) == PLAYER2){
				max1 = 0;
				max2++;
				if(max2 == N)
					player2_win = true;
			}
			else {
				max1 = 0;
				max2 = 0;
			}
		}
	}

	if (player1_win && player2_win)
		return TIE;
	if (player1_win)
		return PLAYER1;
	if (player2_win)
		return PLAYER2;

	return NOCONNECTION;
}

int Board::checkVertically(){
	//check each column, vertically
	int max1 = 0;
	int max2 = 0;
	bool player1_win = false;
	bool player2_win = false;

	for(int j=0; j < this->width; j++) {
		max1 = 0;
		max2 = 0;
		for(int i = 0; i < this->height; i++) {
			if(get(i, j) == PLAYER1) {
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(get(i, j) == PLAYER2) {
				max1 = 0;
				max2++;
				if(max2 == N)
					player2_win = true;
			}
			else{
				max1 = 0;
				max2 = 0;
			}
		}
	}
	if (player1_win && player2_win)
		return TIE;
	if (player1_win)
		return PLAYER1;
	if (player2_win)
		return PLAYER2;

	return NOCONNECTION;
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
    this->popOutCount[1] = 1;

	for(int i = 0; i < height; i++) {
		for(int j=0; j < width; j++){
			set(i, j, emptyCell);
		}
    }

	numOfDiscsInColumn.resize(width);
}

bool Board::makeMove(int column, int operation, Player *p) {
    if (operation == DROP) {
        if (this->canDropADiscFromTop(column, operation)) {
			this->dropADiscFromTop(column, p->getNumber());
            return true;
		}
        else
            return false;
    }
	else if (operation== POPOUT) {
        if ((this->canRemoveADiscFromBottom(column, p->getNumber())
            && (popOutCount[p->getNumber() - 1] == 0))) {
				this->removeADiscFromBottom(column);
				popOutCount[p->getNumber() - 1] += 1;
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

int Board::isConnectN(){
	int tmp_winner = checkHorizontally();

	if(tmp_winner != NOCONNECTION)
		return tmp_winner;

	tmp_winner = checkVertically();
	if(tmp_winner != NOCONNECTION)
		return tmp_winner;

	tmp_winner = checkDiagonally1();
	if(tmp_winner != NOCONNECTION)
		return tmp_winner;

	tmp_winner = checkDiagonally2();
	if(tmp_winner != NOCONNECTION)
		return tmp_winner;

	return NOCONNECTION;
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
	 printBoard();
	 int tmp_winner= checkDiagonally1();
	 printf("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=-x+k
* */
void Board::test2(){
	setBoard(1, 2, PLAYER1);
	setBoard(2, 3, PLAYER1);
	setBoard(3, 4, PLAYER1);
	printBoard();
	int tmp_winner= checkDiagonally1();
	//int tmp_winner= isConnectN();
	printf("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=x-k
* */
void Board::test3(){
	// setBoard(2, 5, PLAYER2);
	// setBoard(4, 3, PLAYER2);
	// setBoard(3, 4, PLAYER2);
	setBoard(5, 4, PLAYER1);
	setBoard(4, 5, PLAYER1);
	setBoard(3, 6, PLAYER1);
	printBoard();
	int tmp_winner= checkDiagonally2();
	//int tmp_winner= isConnectN();
	printf("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=-x+k
* */
void Board::test4(){
	setBoard(2, 0, PLAYER1);
	setBoard(3, 1, PLAYER1);
	// setBoard(4, 2, PLAYER1);
	setBoard(5, 3, PLAYER1);
	printBoard();
	int tmp_winner= checkDiagonally1();
	//int tmp_winner= isConnectN();
	printf("Winner: %d\n", tmp_winner);
}

/**
* test should ends with tie
* */
void Board::test5(){
	setBoard(2, 0, PLAYER1);
	setBoard(3, 1, PLAYER1);
	setBoard(4, 2, PLAYER1);
	// setBoard(1, 4, PLAYER1);

	// setBoard(3, 1, PLAYER1);
	// setBoard(3, 2, PLAYER1);
	// setBoard(3, 3, PLAYER1);
	// setBoard(3, 4, PLAYER1);

	setBoard(0, 3, PLAYER2);
	setBoard(2, 5, PLAYER2);
	setBoard(2, 3, PLAYER2);
	setBoard(1, 4, PLAYER2);
	printBoard();
	// int tmp_winner= this->checkHorizontally();
	int tmp_winner= this->checkDiagonally1();
	printf("Winner: %d\n", tmp_winner);
}
