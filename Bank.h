#ifndef _BANK_
#define _BANK_

class Bank{
 private:
  Property** propertyList;
 public:
  Bank();
  Bank(ifstream &b);
  Property getProperty(Space s);
}

#endif
