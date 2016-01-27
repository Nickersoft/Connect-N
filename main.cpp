//
//  Connect-N
//  ---------
//
//  Created by Tyler Nickerson on 1/17/16.
//  Copyright © 2016 Tyler Nickerson. Most rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "board.h"
#include "player.h"
#include "tools.h"

int main(int argc, const char * argv[]) {

    // Remove both log files
    remove("debug.log");
    remove("error.log");

    // Create a new player and wait for input
    Player *p = new Player();
    cout << p->getName() << endl;
    while(true) {
        p->processInput();
    }
}
