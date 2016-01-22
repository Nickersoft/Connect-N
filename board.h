#ifndef __BOARD_INCLUDED__
#define __BOARD_INCLUDED__

#include <iostream>
#include <vector>

class Player;

#include "player.h"
#include "tools.h"

using namespace std;
using namespace Tools;

class Board {

private:
    int                     get(int, int);
    void                    set(int, int, int);

    bool                    canDropADiscFromTop(int, int);
    bool                    canRemoveADiscFromBottom(int, int);
    int                     checkHorizontally();
    int                     checkVertically();
    int                     checkDiagonally1();
    int                     checkDiagonally2();
    void                    dropADiscFromTop(int, int);
    void                    removeADiscFromBottom(int);
    vector< vector<int> >   resize_layout(vector< vector<int> >, int, int);
    void                    setBoard(int row, int col, int);

public:
        int width,
            height,
            N;

        vector< vector<int> >   layout;
        vector<int>             numOfDiscsInColumn;
        vector<int>             popOutCount;

        Board(int, int, int);
        Board(const Board&);

        bool    isFull();
        int     isConnectN();
        bool    makeMove(int, int, Player*);
        void    printBoard();
        void    printBoard(bool);
        void    test1();
        void    test2();
        void    test3();
        void    test4();
        void    test5();
};
#endif
