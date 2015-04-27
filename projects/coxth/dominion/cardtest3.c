/******************************
* cardtest1.c 
* Thomas Cox
* steward test -  Steward gives you a choice of whether to use it as a trasher,
                  a terminal Silver, or terminal card draw.
* 4/23/2015
******************************/

#include "dominion_helpers.h"
#include "dominion.h"
#include "interface.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int main(int argc, char** argv){
  struct gameState g;
  int i;
  srand(time(NULL));
  int cardPlays;
  int seed = 0;
  int handPos = 0;
  int randomChoice1, randomChoice2 = 0, randomChoice3 = 0;
  
  int randomPlayer;
  
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
  
  cardPlays = 10;
  seed = (rand() % 65535);
  
  
  initializeGame(4,k,seed,&g);
  

  for(i = 0; i < cardPlays; i ++){
    randomPlayer = (rand() % 4);
    randomChoice2 = 0;
	randomChoice3 = 0;
    handPos = (rand() % 5);
    randomChoice1 = (rand() % 3) + 1;
	
	if(randomChoice1 == 3){
	  do{
	    randomChoice2 = (rand() % 5);
	  } while(randomChoice2 == handPos);
	  do{
	    randomChoice3 = (rand() % 5);
	  } while(randomChoice3 == handPos || randomChoice3 == randomChoice2);
	}
	printf("choice1 = %d\n",randomChoice1);
	printf("coins before %d\n", g.coins);
	printf("handcount before %d\n", g.handCount[randomPlayer]);
	stewardCard(&g, handPos, randomPlayer, randomChoice1, randomChoice2, randomChoice3);
	printf("coins after %d\n", g.coins);
	printf("handcount after %d\n", g.handCount[randomPlayer]);
	
  }
   
   printf("all test passed");

   return 0;
}