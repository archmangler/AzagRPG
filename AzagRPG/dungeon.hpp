#include "room.cpp"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon {
  public:
    const int rows = 10;
    const int cols = 10;
    room rooms[10][10];

    void setUpDungeon();
};

#endif
