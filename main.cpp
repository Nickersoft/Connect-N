//
//  main.cpp
//  Connect-N
//
//  Created by Tyler Nickerson on 1/17/16.
//  Copyright © 2016 Tyler Nickerson. All rights reserved.
//

#include <iostream>

#include "main.h"
#include "board.h"

int main(int argc, const char * argv[]) {
    Player *p = new Player();
    cout << p->getName() << endl;
    while(true) {
        p->processInput();
    }
}
