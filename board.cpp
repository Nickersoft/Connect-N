#include "board.h"

/*********************
   PRIVATE FUNCTIONS
**********************/

vector< vector<int> > resize_board(vector< vector<int> > board, int new_width, int new_height) {
    board.resize(new_height);
    for (int i = 0; i < new_height; ++i)
        board[i].resize(new_width);
    return board;
}

int Board::get(int x, int y) {
	return board.at(x).at(y);
}

void Board::set(int row, int col, int new_value) {
	board.at(row).at(col) = new_value;
}

/********************
   PUBLIC FUNCTIONS
*********************/

Board::Board(const Board &rhs) {
    this->board = rhs.board;
}

Board::Board(int height, int width, int N) {

    emptyCell = 9;
    PLAYER1 = 1;
    PLAYER2 = 2;
    NOCONNECTION = -1;
    TIE = 0;

	this->width  = width;
	this->height = height;
	board = resize_board(board, width, height);

	for(int i = 0; i < height; i++) {
		for(int j=0; j < width; j++){
			board[i][j] = this->emptyCell;
		}
    }

	numOfDiscsInColumn.resize(this->width);

//		for(int j=0;j<width;j++)
//			numOfDiscsInColumn[j]=0;
	this->N = N;
 }

int Board::getHeight() {
 	return height;
 }

int Board::getWidth() {
	return width;
}

void Board::printBoard() {
	println("Board: ");
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			printf("%d ", this->get(i, j));
		}
		println();
	}
}

bool Board::canRemoveADiscFromBottom(int col, int currentPlayer) {
	if (col < 0 || col >= this->width) {
		println("Illegal column!");
		return false;
	}
	else if (board[height-1][col] != currentPlayer) {
		printf("You don't have a checker in column %d to pop out!\n", col);
		return false;
	}
	else {
		return true;
	}
}

void Board::removeADiscFromBottom(int col) {
	int i;
	for(i = height - 1; i > height - this->numOfDiscsInColumn.at(col); i--) {
		this->set(i, col, this->get(i-1, col));
	}
	this->set(i, col, emptyCell);
	numOfDiscsInColumn.at(col) -= 1;
}

bool Board::canDropADiscFromTop(int col, int currentPlayer) {
	if(col < 0 || col >= this->width) {
		println("Illegal column!");
		return false;
	}
	else if(this->numOfDiscsInColumn.at(col) == this->height) {
		println("Column is already full. Cannot drop more disc in it.");
		return false;
	}
	else {
		return true;
	}
}

void Board::dropADiscFromTop(int col, int currentplayer) {
	int firstEmptyCellRow = height - this->numOfDiscsInColumn.at(col) - 1;
	this->set(firstEmptyCellRow, col, currentplayer);
	this->numOfDiscsInColumn.at(col) += 1;
}

/**
  * Check if one of the players gets N checkers in a row (horizontally, vertically or diagonally)
  * @return the value of winner. If winner=-1, nobody win and game continues; If winner=0/TIE, it's a tie;
  * If winner=1, player1 wins; If winner=2, player2 wins.
*/

int Board::isConnectN(){
	int tmp_winner = checkHorizontally();

	if(tmp_winner != this->NOCONNECTION)
		return tmp_winner;

	tmp_winner = checkVertically();
	if(tmp_winner != this->NOCONNECTION)
		return tmp_winner;

	tmp_winner = checkDiagonally1();
	if(tmp_winner != this->NOCONNECTION)
		return tmp_winner;

	tmp_winner = checkDiagonally2();
	if(tmp_winner != this->NOCONNECTION)
		return tmp_winner;

	return this->NOCONNECTION;
}

int Board::checkHorizontally() {
	int max1 = 0;
	int max2 = 0;
	bool player1_win = false;
	bool player2_win = false;

	//check each row, horizontally
	for(int i = 0; i < this->getHeight(); i++) {
		max1 = 0;
		max2 = 0;
		for(int j = 0;j < this->getWidth(); j++) {
			if(this->get(i, j) == PLAYER1){
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(this->get(i, j) == PLAYER2){
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

	for(int j=0; j < this->getWidth(); j++) {
		max1 = 0;
		max2 = 0;
		for(int i = 0; i < this->getHeight(); i++) {
			if(this->get(i, j) == PLAYER1) {
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(this->get(i, j) == PLAYER2) {
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
		int x,y;
		if(k < width)
			x = k;
		else
			x = width-1;
		y = -x+k;

		while(x >= 0  && y < height){
			// System.out.println("k: "+k+", x: "+x+", y: "+y);
			if(this->get(height - 1 - y, x) == PLAYER1) {
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(this->get(height - 1 - y, x) == PLAYER2) {
				max1 = 0;
				max2++;
				if(max2 == N)
					player2_win = true;
			}
			else{
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
	// System.out.println("lower: "+lower_bound+", upper_bound: "+upper_bound);
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
			// System.out.println("k: "+k+", x: "+x+", y: "+y);
			if(this->get(height - 1 - y, x) == PLAYER1) {
				max1++;
				max2 = 0;
				if(max1 == N)
					player1_win = true;
			}
			else if(this->get(height - 1 - y, x) == PLAYER2) {
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

bool Board::isFull() {
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++) {
			if(this->get(i, j) == this->emptyCell)
				return false;
		}
	return true;
}

void Board::setBoard(int row, int col, int player) {
	if(row >= height || col >= width)
		println("The row or column number is out of bound!");
	if(player != PLAYER1 && player != PLAYER2)
		println("Wrong player!");
	this->set(row, col, player);
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
	setBoard(1, 2, this->PLAYER1);
	setBoard(2, 3, this->PLAYER1);
	setBoard(3, 4, this->PLAYER1);
	printBoard();
	int tmp_winner= checkDiagonally1();
	//int tmp_winner= isConnectN();
	printf("Winner: %d\n", tmp_winner);
}

/**
* test is connect N diagonally y=x-k
* */
void Board::test3(){
	// setBoard(2, 5, this->PLAYER2);
	// setBoard(4, 3, this->PLAYER2);
	// setBoard(3, 4, this->PLAYER2);
	setBoard(5, 4, this->PLAYER1);
	setBoard(4, 5, this->PLAYER1);
	setBoard(3, 6, this->PLAYER1);
	printBoard();
	int tmp_winner= checkDiagonally2();
	//int tmp_winner= isConnectN();
	printf("Winner: %d\n", tmp_winner);
}


/**
* test is connect N diagonally y=-x+k
* */
void Board::test4(){
	setBoard(2, 0, this->PLAYER1);
	setBoard(3, 1, this->PLAYER1);
	// setBoard(4, 2, this->PLAYER1);
	setBoard(5, 3, this->PLAYER1);
	printBoard();
	int tmp_winner= checkDiagonally1();
	//int tmp_winner= isConnectN();
	printf("Winner: %d\n", tmp_winner);
}

/**
* test should ends with tie
* */
void Board::test5(){
	setBoard(2, 0, this->PLAYER1);
	setBoard(3, 1, this->PLAYER1);
	setBoard(4, 2, this->PLAYER1);
	// setBoard(1, 4, this->PLAYER1);

	// setBoard(3, 1, this->PLAYER1);
	// setBoard(3, 2, this->PLAYER1);
	// setBoard(3, 3, this->PLAYER1);
	// setBoard(3, 4, this->PLAYER1);

	setBoard(0, 3, this->PLAYER2);
	setBoard(2, 5, this->PLAYER2);
	setBoard(2, 3, this->PLAYER2);
	setBoard(1, 4, this->PLAYER2);
	printBoard();
	// int tmp_winner= this->checkHorizontally();
	int tmp_winner= this->checkDiagonally1();
	printf("Winner: %d\n", tmp_winner);
}
