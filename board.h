#ifndef __BOARD_INCLUDED__
#define __BOARD_INCLUDED__
#include <iostream>
#include <vector>

#include "tools.h"

using namespace std;
using namespace Tools;

class Board {

private:
    int width,
        height,
        N,
        emptyCell,
        PLAYER1,
        PLAYER2,
        NOCONNECTION,
        TIE;

        int     get(int, int);
        void    set(int, int, int);

public:
        vector< vector<int> >   board;
        vector<int>             numOfDiscsInColumn;

        Board(const Board&);
        Board(int, int, int);

        int     getWidth();
        int     getHeight();

        bool    canDropADiscFromTop(int, int);
        bool    canRemoveADiscFromBottom(int, int);
        int     checkHorizontally();
        int     checkVertically();
        int     checkDiagonally1();
        int     checkDiagonally2();
        void    dropADiscFromTop(int, int);
        bool    isFull();
        int     isConnectN();
        void    printBoard();
        void    removeADiscFromBottom(int);
        void    setBoard(int row, int col, int);
        void    test1();
        void    test2();
        void    test3();
        void    test4();
        void    test5();
};
#endif
