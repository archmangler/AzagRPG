//
//  player.cpp
//  AzagRPG
//
//  Created by Traiano on 23/2/24.
//

#include "player.hpp"

Player::Player(std::string _name, int _health, int _damage): GameCharacter(_name, _health, _damage){};

void Player::heal(int amount){
    
    currentHealth+= amount;
    if(currentHealth >maxHealth){
        currentHealth = maxHealth;
    }
};

void Player::moveToRoom(room * newRoom) {
    previousRoom = currentRoom;
    currentRoom = newRoom;
};

void Player::retreat(){
    
    room * tempRoom = currentRoom;
    currentRoom = previousRoom;
    previousRoom = tempRoom;
};

void Player::pickUpItem(item item) {
    damage += item.damage;
    heal(item.health); //we can use the heal function here - it's the same functionality as used for the GameCharacter.
}
