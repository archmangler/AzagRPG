# A simple text-based dungeon crawler in object oriented c++ that grew completely out of hand ...


## compiling from Apple's XCode IDE:

```
traiano@Traianos-iMac AzagRPG % ls -l
total 8
drwxr-xr-x  14 traiano  staff  448 Feb 28 22:52 AzagRPG
drwxr-xr-x@  5 traiano  staff  160 Feb 26 23:52 AzagRPG.xcodeproj
-rw-r--r--   1 traiano  staff   98 Feb 28 22:41 README.md
drwxr-xr-x@  6 traiano  staff  192 Feb 28 23:04 build

traiano@Traianos-iMac AzagRPG % xcodebuild -project ../AzagRPG.xcodeproj

```

* This leaves the compiled binaryu in `build/.../Release/AzagRPG`

(Or just use the damn GUI)

## Simple play through:

* the initial starting point of the rpg was as simple as the example below:
* Yeah, it's not exactly FinalFantasy VII but we all have to start somewhere ;-)

```
traiano@Traianos-iMac % ./build/Release/AzagRPG
Welcome to the dungeon. What is your name?
troy
Good luck, troy! Beware, there are many enemies in the dungeon but also some items that may come in handy

Where do you want to go next?
1. Move left
2. Move up
1
You are now in room 2 1
There is an enemy Bat in this room! What would you like to do?
1. Engage enemy
2. Retreat
1
You strike the Bat, dealing 10 damage.
You have defeated the Bat!
Where do you want to go next?
1. Move left
2. Move up
3. Move right
1
You are now in room 2 0
Where do you want to go next?
1. Move up
2. Move right
1
You are now in room 1 0
Where do you want to go next?
1. Move up
2. Move right
3. Move down
2
You are now in room 1 1
You find a Healing Potion in this room! What would you like to do?
1. Pick up item
2. Ignore item
1
You picked up a Healing Potion. Your health is now 100 and your damage is now 10.
Where do you want to go next?
1. Move left
2. Move up
3. Move right
4. Move down
2
You are now in room 0 1
Where do you want to go next?
1. Move left
2. Move right
3. Move down
1
You are now in room 0 0
There is an enemy Troll in this room! What would you like to do?
1. Engage enemy
2. Retreat
1
You strike the Troll, dealing 10 damage.
You have defeated the Troll!
Congratulations, you have reached the exit and are free of the dungeon! Farwell Traiano!

```
