#include <iostream>
#include <vector>

using namespace std;

class Board {

    public:

        int width,
            height,
            N,
            emptyCell,
            PLAYER1,
            PLAYER2,
            NOCONNECTION,
            TIE;


        vector< vector<int> > board;
        vector<int> numOfDiscsInColumn;

        Board(int, int, int);

};
