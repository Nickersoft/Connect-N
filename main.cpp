//
//  main.cpp
//  Connect-N
//
//  Created by Tyler Nickerson on 1/17/16.
//  Copyright © 2016 Tyler Nickerson. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "board.h"
#include "player.h"
#include "tools.h"

int main(int argc, const char * argv[]) {
    remove("debug.log");
    remove("error.log");
    Player *p = new Player();
    cout << p->getName() << endl;
    while(true) {
        p->processInput();
    }
    // srand(time(0));
    // for (int i = 0; i < 100; i++)
    //     std::cout << rand() % 2;
    // Board* b1 = new Board(6, 7, 4);
    // b1->test1();
    // b1->test2();
    // b1->test3();
    // b1->test4();
    // b1->test5();
}
