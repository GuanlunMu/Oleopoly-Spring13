#include<iostream>
using namespace std;
#include "Space.h"

extern int diceTotal;

Space::Space(istream &b)
{
  //sets develpoment bools to false
  hasHotel=false;
  hasHouse4=false;
  hasHouse3=false;
  hasHouse2=false;
  hasHouse1=false;
  hasColor=false;
  //sets the owner to -1 to show that it is unowned
  owner=-1;
  //set the basic information for each space:
  b >> position;    
  //load type and assign each of them a correspoding type boolean
  if (position == 0)
    goSpace = true;
  else if (position == 2 || position == 17 || position == 33)
    comChestSpace = true;
  else if(position == 7 || position == 22 || position == 36)
    chanceSpace = true;
  else if (position == 4 || position == 38)
    taxSpace = true;
  else if (position == 10)
    jailSpace = true;
  else if (position == 30)
    gotojailSpace = true;
  else if (position == 20)
    freeParkingSpace = true;
  else 
    propertySpace = true;
  name = new char [64];
  b >> name;
  b >> x_cord >> y_cord;
  b >> group >> price >> mortgageValue >> rent >> rentHouse1 >> rentHouse2;
  b  >> rentHouse3>> rentHouse4 >> rentHotel >> hotel_price;

  
}

int Space::calculateRentOwed(Player *p){
  cout<<"CALCULATE RENT OWED FUNCTION"<<endl;
  // if(!hasColor){
    checkHasColor(p);
    cout<<"checkHasColor="<<hasColor<<endl;
    // }
  int rentOwed;
  cout<<"group number: "<<group<<endl;
  if(group==10){ 
    cout<<"Railroad Rent"<<endl;//Rail Roads
    cout<<"Num railroads: "<<p->numRailroads<<endl;
    switch (p->numRailroads){
    case 1:
      rentOwed=25; break;
    case 2:
      rentOwed=50; break;
    case 3:
      rentOwed=100; break;
    case 4:
      rentOwed=200; break;
    }
  }
  else if (group==9){             //Utility
    if(hasColor)
      rentOwed=10*diceTotal;
    else
      rentOwed=4*diceTotal;
    }
 else{                            //Property
   if(hasHotel)
     rentOwed=rentHotel;
   else if(hasHouse4)
     rentOwed=rentHouse4;
   else if(hasHouse3)
     rentOwed=rentHouse3;
   else if(hasHouse2)
     rentOwed=rentHouse2;
   else if(hasHouse1)
     rentOwed=rentHouse1;
   else if(hasColor)
     rentOwed=2*rent;
   else
      rentOwed=rent;
  }
  return rentOwed;
}

void Space::develop(Player* p){
  if(group==10 ||group==9){
    cout<<"RRUTILITY"<<endl;
    return;
  }

  if(p->checkCanPay(hotel_price)){
    if(propertySpace){
      if(hasHotel){
	cout<<"Has Hotel"<<endl;
	return;
      }
      else if(hasHouse4){
	hasHouse4=false;
	hasHotel=true;
      }
      else if(hasHouse3){
	hasHouse3=false;
	hasHouse4=true;
      }
       else if(hasHouse2){
	hasHouse2=false;
	hasHouse3=true;
      }
       else if(hasHouse1){
	hasHouse1=false;
	hasHouse2=true;
      }
      /*
       else if(hasColor){
	 hasHouse1=true;
      }
      */
       else{
	hasHouse1=true;
       }
      p->adjustBalance(-hotel_price);
    }
  }
}

void Space::mortgage(Player &p){
  p.adjustBalance(mortgageValue);
  isMortgaged=true;
}

void Space::unmortgage(Player &p){
  int value=mortgageValue*1.1;
  if(p.checkCanPay(value)){
    isMortgaged=false;
    p.adjustBalance(-value);
  }
}


bool Space::checkHasColor(Player *p){
  int prop1, prop2, prop3,prop4;
  prop1=prop2=prop3=prop4=-1;
  switch(group){
  case 10://Rail Roads
    prop1=5;
    prop2=15;
    prop3=25;
    prop4=35;
    break;
  case 1:
   prop1=1;
   prop2=3;
   break;
  case 2:
    prop1=6;
    prop2=8;
    prop3=9;
    break;
  case 3:
    prop1=11;
    prop2=13;
    prop3=14;
    break;
  case 4:
    prop1=16;
    prop2=18;
    prop3=19;
    break;
  case 5:
    prop1=21;
    prop2=23;
    prop3=24;
    break;
  case 6:
    prop1=26;
    prop2=27;
    prop3=29;
    break;
  case 7:
    prop1=31;
    prop2=32;
    prop3=34;
    break;
  case 8:
    prop1=37;
    prop2=39;
    break;
  case 9:
    prop1=12;
    prop2=28;
  }
  if(prop4!=-1){//Rail Road
    p->numRailroads=0;
    if(p->myProperties[prop1])
      p->numRailroads++;
    if(p->myProperties[prop2])
      p->numRailroads++;
    if(p->myProperties[prop3])
      p->numRailroads++;
    if(p->myProperties[prop4])
      p->numRailroads++;
  }
  else if(prop3==-1){//Two properties in group (First and Last)
    if(p->myProperties[prop1] && p->myProperties[prop2])
      hasColor=true;
  }
  else{
    if(p->myProperties[prop1] && p->myProperties[prop2] && p->myProperties[prop3])
      hasColor=true;
  }
  return hasColor;
}
