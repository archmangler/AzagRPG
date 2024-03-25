#include "room.cpp"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon {
  public:
    const int rows = 5;
    const int cols = 5;
    room rooms[5][5];

    void setUpDungeon();
};

#endif
