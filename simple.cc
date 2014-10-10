/* Simple simulator for Chutes and Ladders. */

#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>

using std::map;


map<int,int> jumpTable;

void initializeJumpTable() {

  /* Initialize. */
  for(int i = 1; i <= 100; ++i) {
    jumpTable[i] = 0;
  }

  /* Ladders. */
  jumpTable[1] = 38;
  jumpTable[4] = 14;
  jumpTable[9] = 31;
  jumpTable[21] = 42;
  jumpTable[28] = 84;
  jumpTable[36] = 44;
  jumpTable[51] = 67;
  jumpTable[71] = 91;
  jumpTable[80] = 100;

  /* Chutes */
  jumpTable[16] = 6;
  jumpTable[48] = 26;
  jumpTable[49] = 11;
  jumpTable[56] = 53;
  jumpTable[62] = 19;
  jumpTable[64] = 60;
  jumpTable[87] = 24;
  jumpTable[93] = 73;
  jumpTable[95] = 75;
  jumpTable[98] = 78;

  return;
}

const int iterationCount = 100;

int main(void) {

  initializeJumpTable();
  /* Random number code based on cppreference.com example. */
  std::vector<int> turnList;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1,6);
  /* Now can call dis(gen) to get a dice roll */

  /* Basic game loop. */
  int currLoc = 0;
  int steps = 0;
  int newLoc = 0;
  int roll = 0;

  unsigned long int sum = 0;

  for(int i = 0; i < iterationCount; ++i) {
    currLoc = steps = newLoc = roll = 0;
    for(;;) {
      ++steps;
      roll = 0;
      roll = dis(gen);
      std::cout << "current: " << currLoc << std::endl;
      std::cout << "roll: " << roll << std::endl;
      /* Must land on 100 exactly. */
      if((currLoc == 100) || ((currLoc + roll) == 100)) {
	break;
      } else if((currLoc + roll) > 100) {
	continue;
      } else {
	currLoc += roll;
	newLoc = 0;
	newLoc = jumpTable.at(currLoc);
	if(newLoc != 0) {
	  std::cout << "Hit in jumpTable: " << newLoc << std::endl;
	  currLoc = newLoc;
	}
      } /* if */
    } /* for(;;) */
    turnList.push_back(steps);
  } /* for(int i) */
  std::sort(turnList.begin(),turnList.end());
  std::cout << "Smallest turn count = " << turnList[0] << std::endl;
  std::cout << "Average turn count = " 
	    << (std::accumulate(turnList.begin(),
				turnList.end(),
				0) / turnList.size()) 
	    << std::endl;
  
  return 0;
}

