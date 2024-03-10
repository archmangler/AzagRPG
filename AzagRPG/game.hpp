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
    
    void printDungeonLayout(); //print out the current map status of the dungeon
    void handleMovementActions(); //
    void printActions(std::vector<std::string>); //
    void initiateRoomSequence(); //
    void handleEnemyActions();
    void engageInCombat();
    void handleItemActions();
    void updateDungeonMapEnemies(room * currentRoom); //update the location of novel artifacts and events on the map
    
};


#endif /* game_hpp */
