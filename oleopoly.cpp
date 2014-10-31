#include<iostream>
using namespace std;
#include "Board.h"
#include "Player.h"

int main()
{
  //Set Up Board
  Board board("boardsetup.txt");
  bool gameNotFinished=true;
  int numPlayers;
  //Get number of Players from Menu
  Player* playerList= new Player[numPlayers];
  for(int i=0; i<numPlayers; i++)
    playerList[i].setBeginning();
  bool stillIn;
  Player* temp;
  //Loop turns until the game ends
  int currentPlayer=0;
  int i=0;
  while(gameNotFinished){
    playerList[currentPlayer].takeTurn();
    //Check If Player Is Still In Game
    //Proto Only
    i++;
    if(i<10)
      gameNotFinished=false;
  }
  return 0;
}
