#include<iostream>
#include "Board.h"
using namespace std;

int main()
{
  Board game("boardsetup.txt");
  for (int i = 0; i < 40; i++)
    {
      cout << game.board[i] -> name << " " << game.board[i] -> position << " ";
    }
  return 0;
}
