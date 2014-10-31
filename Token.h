#ifndef _TOKEN_
#define _TOKEN_
#include "Position.h"

class Token{
  Position pos;
 public:
  void move(int n);
  void setPosition(Position p);
  bool active;
};

#endif
