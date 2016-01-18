//
//  main.cpp
//  Connect-N
//
//  Created by Tyler Nickerson on 1/17/16.
//  Copyright © 2016 Tyler Nickerson. All rights reserved.
//

#include <iostream>

#include "main.h"

int main(int argc, const char * argv[]) {
    Board::Board* board = new Board::Board(6, 7, 4);
    std::cout << board->width << std::endl;
}
