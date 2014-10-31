#ifndef _SPACE_
#define _SPACE_
#include<iostream>
#include "Player.h"
using namespace std;



class Space
{
 public: 
  int owner;
  int position;
  char* name;
  int group;
  int price;
  int mortgageValue;
  int rent;
  int rentHouse1;
  int rentHouse2;
  int rentHouse3;
  int rentHouse4;
  int rentHotel;
  int hotel_price;
  int x_cord, y_cord;
  bool goSpace;
  bool jailSpace;
  bool propertySpace;
  bool chanceSpace;
  bool comChestSpace;
  bool taxSpace;
  bool freeParkingSpace;
  bool gotojailSpace;
  int spaceType;
 public:
  Space(istream &b);
  void drawSpace(int p);
  int calculateRentOwed(Player *p);
  bool hasHotel;
  bool hasHouse4;
  bool hasHouse3;
  bool hasHouse2;
  bool hasHouse1;
  bool hasColor;
  void develop(Player *p);
  void mortgage(Player &p);
  void unmortgage(Player &p);
  bool isMortgaged;
  bool checkHasColor(Player *p);
  //int railroads;
};

#endif
