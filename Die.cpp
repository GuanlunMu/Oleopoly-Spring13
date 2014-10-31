#include <stdlib.h>
#include <ctime>
using namespace std;
#include "Die.h"

Die::Die()
{
srand(static_cast<unsigned int>(time(0)));
}


void Die::roll(){
  d1= rand() %6 +1;
  d2= rand() %6 +1;
}
int Die::getTotal()
{
  return d1+d2;
}

bool Die::checkIsDouble()
{
  if(d1==d2)
    {
      numDoubles++;
      return true;
    }
  return false;
}

void Die::resetDoublesCount()
{
  numDoubles=0;
}
