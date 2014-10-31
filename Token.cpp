#include "Token.h"

void Token::setPosition(Position p){
  pos.x=p.x;
  pos.y=p.y;
}

void Token::move(Board &b, int spaceNum){
  Position temp= b.getTokenPosition(spaceNum);
  pos.x=temp.x;
  pos.y=temp.y;
}
