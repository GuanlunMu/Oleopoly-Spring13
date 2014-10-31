#ifndef _PLAYER_
#define _PLAYER_
#include<GL/glut.h>
#include <math.h> 
#include "Die.h"
//#include "Board.h"
class Board;

class Player
{
 public:
 int balance;
  int width, height;
  bool myProperties[40];
  int x, y;
  int position;
int propertyNo;
  Player(Board &game);
  void update(Board &game, int dieTotal);
  void adjustBalance(int amt);
   void takeTurn(Board &game);
  int getBalance();
  bool GOOJailFree;
  void buyProperty(int pos, Board &game);
  void recieveProperty(int pos,Board &game);
  bool checkCanPay(int amt);
  int getPropertyNo();
  int numRailroads;
};

#endif
