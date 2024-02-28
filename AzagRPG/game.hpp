//
//  game.hpp
//  AzagRPG
//
//  Created by Traiano on 23/2/24.
//



#include <stdio.h>
#include "dungeon.hpp"
#include "player.hpp"

#include <vector>

#ifndef GAME_HPP
#define GAME_HPP

class Game{
private:
    Dungeon * dungeon;
    Player * player;
public:
    bool isGameOver; //check to see if the game is over.
    Game(Player *, Dungeon *);
    
    std::vector<std::string> getMovementActions(); //
    
    void handleMovementActions(); //
    void printActions(std::vector<std::string>); //
    void initiateRoomSequence(); //
    void handleEnemyActions();
    void engageInCombat();
    void handleItemActions();
    
};


#endif /* game_hpp */
