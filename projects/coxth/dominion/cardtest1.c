/******************************
* cardtest1.c 
* Thomas Cox
* smithy test
* 4/23/2015
******************************/

#include "dominion_helpers.h"
#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv){
  struct gameState g;
  int i;
  srand(time(NULL));
  int cardPlays;
  int seed = 0;
  int handPos = 0;
  
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
  
  cardPlays = 10;
  seed = (rand() % 65535);
  
  initializeGame(2,k,seed,&g);
  
  for(i = 0; i < cardPlays; i ++){
    g.whoseTurn = 0;
	handPos = (rand() % g.handCount[0]);
	printf("g.handcount = %d\n",g.handCount[0]);
	smithyCard(&g, handPos, 0);
	printf("g.handcount = %d\n",g.handCount[0]);
  }
   return 0;

  
}
  