//
//  game.cpp
//  AzagRPG
//
//  Created by Traiano on 23/2/24.
//

#include "game.hpp"
#include <iostream>

Game::Game(Player * _player, Dungeon * _dungeon){
    
    player = _player;
    dungeon = _dungeon;
    isGameOver = false;
    
    dungeon ->setUpDungeon();
    
    player->currentRoom = &dungeon->rooms[dungeon->rows-1][dungeon->cols-1];
        
}

void Game::initiateRoomSequence() {
    
    room * room = player->currentRoom;
    
    if(room->row == 0 && room->col == 0 && room->enemies.empty()) {
        std::cout << "congratulations! you have reached the exit and are free of the dungeon, farewell! \n" << player->getName() << "!\n";
        isGameOver = true;
        return;
    }
    
    if(!player->currentRoom->enemies.empty()){
        handleEnemyActions();
    }else if(!player->currentRoom->items.empty()){
        handleItemActions();
    }else{
        handleMovementActions();
    }
}

std::vector<std::string> Game::getMovementActions(){
    
    std::vector<std::string> actions;
    
    room * currentRoom = player->currentRoom;
    
    std::cout << "Current Room Value: \n" << &currentRoom << "\n";

    
    if(currentRoom->col > 0){
        actions.push_back("Move left");
        std::cout << "action matched: " << "Move Left \n";
    }
    if(currentRoom->row > 0){
        actions.push_back("Move up");
        std::cout << "action matched: " << "Move up \n";

    }
    if(currentRoom->col < (dungeon->cols - 1)){
        actions.push_back("Move right");
        std::cout << "action matched: " << "Move right \n";
    }
    if(currentRoom->row < (dungeon->rows - 1)){
        actions.push_back("Move down");
        std::cout << "action matched: " << "Move down \n";
    }
    
    std::cout << "Begin: \n";
    for(int i = 0;i < actions.size();i++){
        std::cout << i+1 << ". " << actions[i] << std::endl;
    }
    
    printActions(actions);
    
    return actions;
};

void::Game::printActions(std::vector<std::string> actions){
    for(int i = 0;i < actions.size();i++){
        std::cout << i+1 << ". " << actions[i] << std::endl;
    }
}

void Game::handleMovementActions() {
    

    
    std::vector<std::string> actions = getMovementActions();
    printActions(actions);
    
    std::cout << "Where do you want to go to next?\n";
    
    int input;
    
    std::cin >> input;
    std::string chosenAction = actions[input-1];
    
    int horizontalMovement = 0;
    int verticalMovement = 0;
    
    if(chosenAction == "Move left") {
        horizontalMovement = -1;
    }
    else if(chosenAction == "Move right") {
        horizontalMovement = 1;
    }
    else if(chosenAction == "Move up") {
        verticalMovement = -1;
    }
    else if(chosenAction == "Move down") {
        verticalMovement = 1;
    }
    
    room * newRoom = &dungeon->rooms[player->currentRoom->row + verticalMovement][player->currentRoom->col + horizontalMovement];
    
    player->moveToRoom(newRoom);
    
    std::cout << "You are now in room " << newRoom->row <<" " <<newRoom->col <<std::endl;
    
    
    
};


void Game::handleEnemyActions() {

    std::cout << "There is an enemy " << player->currentRoom->enemies[0].getName() << " in this room! What would you like to do? \n";
    std::vector<std::string> actions;

    actions.push_back("Engage enemy!");
    actions.push_back("Retreat");

    printActions(actions);

    int input;
    std::cin >> input;
    
    if (input == 1) {
        //engage the enemy
        engageInCombat();
    } else {
        player->retreat();
    };
    
};

void Game::engageInCombat() {
    
    GameCharacter *enemy = &player->currentRoom->enemies[0];
    
    while(true){
        
        enemy->takeDamage(player->getDamage());
        
        std::cout << "You Strike the " <<enemy->getName() << ", dealing " << player->getDamage() << " damage.\n";
        
        if(!enemy->checkIfAlive()){
            std::cout <<"You have defeated the " << enemy->getName();
        } else {
            player->currentRoom->enemies.clear();
            return;
        }
        
        //take some damage
        player->takeDamage(enemy->getDamage());
        
        std::cout << "You take " <<enemy->getDamage() << ", you now have " << player->getDamage() << " damage.\n";
        
        if(!player->checkIfAlive()){
            isGameOver = true;
            std::cout << "\n" << "You have been defeated! Better luck next time!\n" << enemy->getName();
        } else {
            player->currentRoom->enemies.clear();
            return;
        }
        
        //keep fighting or retreat?
        std::cout << "Would you like to keep fighting or retreat?\n" ;
        std::vector<std::string> actions;
     
        actions.push_back("Keep Fighting!");
        actions.push_back("Retreat");
        printActions(actions);
        
        int input;
        std::cin >> input;
            
        if (input != 1) {
            //Engage enemy
            player->retreat();

        }
    }
}

void Game::handleItemActions(){

    item item = player->currentRoom->items[0];

    std::cout << "You find a " << player->currentRoom->items[0].name << " in this room! what would you like to do?\n" ;
    std::vector<std::string> actions;
    
    actions.push_back("Acquire item");
    actions.push_back("Ignore item");
    
    printActions(actions);
    
    int input;
    std::cin >> input;
    if(input == 1) {
        player->pickUpItem(item);
        std::cout << "You acquired a " << item.name << " your health is now: " << player->getHealth() << " and your damage is now " << player->getDamage() << " .\n";
        player->currentRoom->items.clear();
    } else {
        handleMovementActions(); //because at this point the only thing to do is move to another Room.
    };
}



