#ifndef __BOARD_INCLUDED__
#define __BOARD_INCLUDED__

#define emptyCell 9
#define MAXDEPTH 5
#define PLAYER1 1
#define PLAYER2 2
#define NOCONNECTION -1
#define TIE 0
#define DROP 1
#define POPOUT 0

#include <iostream>
#include <map>
#include <vector>

class Player;

#include "player.h"
#include "tools.h"

using namespace std;
using namespace Tools;

struct Move {
    int column;
    int operation;
};

class Board {

private:
    int width,
        height,
        N;

    vector< vector<int> >   layout;
    Move                    lastPlayedMove;
    vector<int>             numOfDiscsInColumn;
    vector<int>             popOutCount;

    int                     get(int, int);
    void                    set(int, int, int);

    bool                    canDropADiscFromTop(int, int);
    bool                    canRemoveADiscFromBottom(int, int);
    map<int, int>           checkDiagonally1(int);
    map<int, int>           checkDiagonally2(int);
    map<int, int>           checkHorizontally(int);
    map<int, int>           checkVertically(int);
    void                    dropADiscFromTop(int, int);
    void                    removeADiscFromBottom(int);
    vector< vector<int> >   resize_layout(vector< vector<int> >, int, int);
    void                    setBoard(int row, int col, int);

public:
        Board(int, int, int);
        Board(const Board&);

        bool            isFull();
        int             isConnectN();
        int             getHeight();
        map<int, int>   getPlays(int);
        Move            getLastPlayed();
        int             getN();
        int             getWidth();
        bool            makeMove(Move, Player*);
        void            printBoard();
        void            printBoard(bool);
        void            test1();
        void            test2();
        void            test3();
        void            test4();
        void            test5();
};
#endif
