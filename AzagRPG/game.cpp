//
//  game.cpp
//  AzagRPG
//
//  Created by Traiano on 23/2/24.
//
#include "game.hpp"
#include <iostream>
#include <map>

Game::Game(Player * _player, Dungeon * _dungeon) {
  player = _player;
  dungeon = _dungeon;
  isGameOver = false;

  dungeon->setUpDungeon();
  player->currentRoom = &dungeon->rooms[dungeon->rows-1][dungeon->cols-1];
}

void Game::initiateRoomSequence() {
  
    room * room = player->currentRoom;
    
  if (room->row == 0 && room->col == 0 && room->enemies.empty()) {
    std::cout << "Congratulations, you have reached the exit and are free of the dungeon! Farwell " << player->getName() << "!\n";
      
      //print the game map one more time
      Game::printDungeonLayout();
      
    isGameOver = true;
    return;
  }

  if (!room->enemies.empty()) {
    handleEnemyActions();
  } else if (!room->items.empty()) {
    handleItemActions();
  } else {
    printDungeonLayout(); //print the dungeon layout in simple text format
    handleMovementActions();
  }
    
}

void Game::printActions(std::vector<std::string> actions) {
  for (int i = 0; i < actions.size(); i++) {
    std::cout << i + 1 << ". " << actions[i] << std::endl;
  }
}

std::vector<std::string> Game::getMovementActions() {
  std::vector<std::string> actions;

  room* currentRoom = player->currentRoom;
  if (currentRoom->col > 0) {
    actions.push_back("Move left");
  }
  if (currentRoom->row > 0) {
    actions.push_back("Move up");
  }
  if (currentRoom->col < (dungeon->cols - 1)) {
    actions.push_back("Move right");
  }
  if (currentRoom->row < (dungeon->rows - 1)) {
    actions.push_back("Move down");
  }
  return actions;
}

void Game::handleMovementActions() {
  std::cout << "Where do you want to go next?\n";
  std::vector<std::string> actions =  getMovementActions();
  printActions(actions);

  int input;
  std::cin >> input;
  std::string chosenAction = actions[input - 1];

  int horizontalMovement = 0;
  int verticalMovement = 0;
  if (chosenAction == "Move left") {
    horizontalMovement = -1;
  } else if (chosenAction == "Move up") {
    verticalMovement = -1;
  } else if (chosenAction == "Move right") {
    horizontalMovement = 1;
  } else if (chosenAction == "Move down") {
    verticalMovement = 1;
  }

  room* newRoom = &dungeon->rooms[player->currentRoom->row + verticalMovement][player->currentRoom->col + horizontalMovement];
  player->moveToRoom(newRoom);

  std::cout << "You are now in room " << newRoom->row << " " << newRoom->col << std::endl;
}

//print the dungeon layout
void Game::printDungeonLayout() {

    int horizontalLoc = 0;
    int verticalLoc = 0;
    //int horizontalLocDeadEnemy = 2;
    //int verticalLocDeadEnemy = 2;
    
    std::map<room*, std::string>::iterator it;

    room * rm; //for iterating through map of room keys
    room * currentRoom = &dungeon->rooms[player->currentRoom->row][player->currentRoom->col];
    horizontalLoc = currentRoom->row;
    verticalLoc = currentRoom->col;

    std::cout << "The Map of Azag lies below:\n\n";

    //FIX this shit!
    //*WARNING* this may not be what you intend!
    for(int i = 0;i <  dungeon->rows ; i++) {
        for(int j = 0; j < dungeon->cols ; j++) {
            if(j == horizontalLoc && i == verticalLoc) {
                std::cout << "  [*]  ";
            }else {
                //if the current iteration has an enemy location
                //update the enemy location
                //else
                //loop through a vector of dead enemies to check if the current coordinate has a defeated enemy in it.
                unsigned long int graveSize = enemyGraveyard.size();
                if(graveSize > 0){
                    for (it = enemyGraveyard.begin(); it != enemyGraveyard.end(); it++) {
                        rm = it->first;
                        if(j == rm->row && i == rm->col) {
                            std::cout << "  [:-(]  ";
                        } else {
                            //std::cout << "  [*]  ";
                            std::cout << "  [?]  ";
                        }
                    }
                } else {
                    std::cout << "  [?]  ";
                }
            }
        }
        std::cout << "\n";
        std::cout << "\n";
        
    }
    
    std::cout << "\n";
    std::cout << "You are here: " << horizontalLoc << ":" <<  verticalLoc <<"\n";
    std::cout << "\n";
    std::cout << "\n";
}

void Game::handleEnemyActions() {
  std::cout << "There is an enemy " << player->currentRoom->enemies[0].getName() << " in this room! What would you like to do?\n";
  std::vector<std::string> actions;
  actions.push_back("Engage enemy");
  actions.push_back("Retreat");
  printActions(actions);

  int input;
  std::cin >> input;
  if (input == 1) {
    engageInCombat();
  } else {
    player->retreat();
  }
    
    //update the location of the enemy after the encounter
    room * currentRoom = &dungeon->rooms[player->currentRoom->row][player->currentRoom->col];
    updateDungeonMapEnemies(currentRoom);

}

void Game::updateDungeonMapEnemies(room * currentRoom){
    //need a dedicated function to update enemy location
    std::string enemy = player->currentRoom->enemies[0].getName();
    std::cout << "\n\n Remembering where our enemy "<< enemy <<" fell :'-( \n\n";
    tendEnemyGraveyard(enemy);
    std::cout <<"\n\n************************************************************** \n\n";
}

void Game::engageInCombat() {
  GameCharacter *enemy = &player->currentRoom->enemies[0];
  while (true) {
    enemy->takeDamage(player->getDamage());
    std::cout << "You strike the " << enemy->getName() << ", dealing " << player->getDamage() << " damage.\n";
    if (!enemy->checkIfAlive()) {
      std::cout << "You have defeated the " << enemy->getName() << "!\n";
      player->currentRoom->enemies.clear();
        //update the enemy graveyard
        
      return;
    }

    player->takeDamage(enemy->getDamage());
    std::cout << "You take " << enemy->getDamage() << " damage. You now have " << player->getHealth() << " health.\n";
    if (!player->checkIfAlive()) {
      isGameOver = true;
      std::cout << "You have been defeated! Better luck next time!\n";
      return;
    }

    std::cout << "Would you like to keep fighting or retreat?\n";
    std::vector<std::string> actions;
    actions.push_back("Keep fighting");
    actions.push_back("Retreat");
    printActions(actions);

    int input;
    std::cin >> input;
    if (input != 1) {
      player->retreat();
      return;
    }
  }
}

void Game::tendEnemyGraveyard(std::string _enemy) {
    //maintain a vector of defeated enemy locations
    room * currentRoom = &dungeon->rooms[player->currentRoom->row][player->currentRoom->col];
    enemyGraveyard.insert(std::make_pair(currentRoom,_enemy));
    std::cout << "Burying enemy " << enemyGraveyard[currentRoom] << " at location " << currentRoom->col << "," << currentRoom->row <<  " R.I.P ..." << std::endl;
}

void Game::handleItemActions() {
  item item = player->currentRoom->items[0];
  std::cout << "You find a " << item.name << " in this room! What would you like to do?\n";
  std::vector<std::string> actions;
  actions.push_back("Pick up item");
  actions.push_back("Ignore item");
  printActions(actions);

  int input;
  std::cin >> input;
  if (input == 1) {
    player->pickUpItem(item);
    std::cout << "You picked up a " << item.name << ". Your health is now " << player->getHealth() << " and your damage is now " << player->getDamage() << ".\n";
    player->currentRoom->items.clear();
  } else {
    handleMovementActions();
  }
}
