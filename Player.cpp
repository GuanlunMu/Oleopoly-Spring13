#include<iostream>
using namespace std;
#include "Player.h"
#include "Board.h"

//void loadPlayerDeedInfo();

void displayDice(int d1, int d2);
extern int turnControl;
extern int diceTotal;

Player::Player(Board &game)
{
  numRailroads=0;
  width = height = 50;
  position = 0;
  balance = 1500;
  x = game.board[position] -> x_cord;
  y = game.board[position] -> y_cord;
  //cout << "the initial cord are " << x << " " << y << endl;
  for(int i=0;i<40;i++)
    myProperties[i]=false;
}

void Player::update(Board &game, int dieTotal)
{
  position += dieTotal;
  if(position>39){
    position -=40;
    adjustBalance(200);
  }
  x = game.board[position] -> x_cord;
  y = game.board[position] -> y_cord;
}

//READ THE COMMENT BELOW
//DO NOT REMOVE THIS FUNCTION
//READ THE COMMENT ABOVE
void Player::takeTurn(Board &game){
  int d1, d2;
  Die dice;
  dice.roll();
  cout<<"\nPlayer "<<turnControl<<endl;
  cout<<"Player Balance: "<<balance<<endl;
  diceTotal = dice.getTotal();
  update(game,diceTotal);
  displayDice(dice.d1, dice.d2);
  game.spaceManager(this);
  }

void Player::adjustBalance(int amt){
  balance+=amt;
}

int Player::getBalance(){
  return balance;
}

void Player::buyProperty(int pos, Board &game){
  cout<<"BP pos "<<pos<<endl;
  adjustBalance(-(game.board[pos])->price);
  recieveProperty(pos,game);
}

void Player::recieveProperty(int pos, Board &game){
  myProperties[pos]=true;
  game.board[pos]->owner=turnControl;
  //loadPlayerDeedInfo();
}

bool Player::checkCanPay(int amt){
  return(getBalance()-amt>=0);
}

int Player::getPropertyNo()
{
  propertyNo = 0;
  for (int i = 0; i < 40; i++)
    {
      if (myProperties[i])
	propertyNo++;
    }
  return propertyNo;
}
