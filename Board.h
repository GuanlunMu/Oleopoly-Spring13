#ifndef _BOARD_
#define _BOARD_
#include "Space.h"

class Player;

class Board
{
 public:
  Space** board;
  Board(const char* filename);
  void spaceManager(Player* p);
};

#endif
