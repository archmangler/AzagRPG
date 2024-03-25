//
//  room.cpp
//  AzagRPG
//
//  Created by Traiano on 23/2/24.
//
//#include <stdio.h>
#include <vector>
#include "gameCharacter.hpp"
#include "item.cpp"

#ifndef ROOM_CPP
#define ROOM_CPP

struct room {
    
    int row;
    int col;
    
    std::vector<GameCharacter> enemies;
    std::vector<item> items;
    
};

#endif
