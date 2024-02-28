#include <iostream>
#include "game.hpp"

int main() {
    
    std::string name;
    
    std::cout << "Welcome to the dungeon. What is your name?\n";
    std::cin >> name;
    
    Player player  = Player("Traiano", 100, 10);
    Dungeon dungeon;
    Game game = Game(&player, &dungeon);
    
    //std::cout << player.getName() << std::endl;
    
    std::cout << "Good luck, " << name << "! Beware, there are many enemies in the dungeon but also some items that may come in handy\n\n";
    
    while(!game.isGameOver){
        game.initiateRoomSequence();
    }
    
    //game.handleMovementActions();
    
}
