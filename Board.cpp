#include<fstream>
#include<iostream>
#include<ctime>
using namespace std;
#include "Board.h"
#include "Player.h"
#include "Cards.h"
//#include "globalVars.h"

void chance(Player *p);
void communityChest(Player *p);
extern Player **playTurn;

Board::Board(const char* filename)
{
  ifstream g(filename);
  board = new Space *[40];
  for(int i = 0; i < 40; i++)
      board[i]= new Space(g);
}





void Board::spaceManager( Player* p){
  int spaceNumber= p->position;
  if(board[spaceNumber]->propertySpace){
    //if unowned
    if(board[spaceNumber]->owner==-1)
      //prompt user purchase
      cout<<"unowned"<<endl;
    else{ //Property is Owned
      int ownerNum= board[spaceNumber]->owner;
      cout<<"\nRENT DUE: ";
      int rentDue=board[spaceNumber]->calculateRentOwed(playTurn[ownerNum]);
      cout<<rentDue<<endl<<endl;
      p->adjustBalance(-rentDue);
      
      playTurn[ownerNum]->adjustBalance(rentDue);
    }
  }
  else if(board[spaceNumber]->chanceSpace){
    chance(p);
   
  }
  else if(board[spaceNumber]->comChestSpace){
    communityChest(p);
  }
  else if(board[spaceNumber]->jailSpace){
    //do nothing
  }
  else if(board[spaceNumber]->gotojailSpace){
    p->position=10;
    if(!p->GOOJailFree){
      p->adjustBalance(-50);
    }
    p->GOOJailFree=false;
  }
  else if(board[spaceNumber]->freeParkingSpace){
    //do nothing
  }
  else if(board[spaceNumber]->goSpace){
    p->adjustBalance(200);
  }

  //return p;
}

