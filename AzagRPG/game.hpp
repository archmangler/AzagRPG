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
#include <map>

class Game{
private:
    Dungeon * dungeon;
    Player * player;
public:
    bool isGameOver; //check to see if the game is over.
    Game(Player *, Dungeon *);
    
    std::vector<std::string> getMovementActions(); //
    std::vector<std::string> enemyHistory(); //TBD vector to keep a history of the enemy's movements through the dungeon
    
    void printDungeonLayout(); //print out the current map status of the dungeon
    void handleMovementActions(); //
    void printActions(std::vector<std::string>); //
    void initiateRoomSequence(); //
    void handleEnemyActions();
    void engageInCombat();
    void handleItemActions();
    void updateDungeonMapEnemies(room * currentRoom); //update the location of novel artifacts and events on the map
    void tendEnemyGraveyard(std::string _enemy); //maintain a list of dead enemies and their locations ([x,y],enemy_name)
   
    void trackPlayerHistory(); //keep track of player's path through the dungeon (see: playerHistory() vector)
    void displayPlayerHistory(); //print out the player journey so fr through the maze construct.
    void quitGame(); //leave
    
    //the rooms we hid the bodies in
    std::map<room*,std::string> enemyGraveyard; //map to keep a map of [room,enemy_name]
    std::vector<room*> playerHistory; //
};


#endif /* game_hpp */
