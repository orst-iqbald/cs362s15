/******************************
* cardtest1.c 
* Thomas Cox
* remodel test - trash a card from your hand . Gain a card costing up to 2 more than the trashed card.
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
  int randomChoice1, randomChoice2 = 0;

  int handCountPre = 0;
  int randomPlayer;
  int cardCost1,cardCost2;
  int validate = 0;
  
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
  
  cardPlays = 100;
  
  
  
  for(i = 0; i < cardPlays; i ++){
    seed = (rand() % 65535);
	initializeGame(4,k,seed,&g);
  
    randomPlayer = (rand() % 4);
    randomChoice2 = 0;
    handPos = (rand() % 5);
	handCountPre = 0;
	
    
	
	do{
	  randomChoice1 = (rand() % 5);
	} while(randomChoice1 == handPos);
	
	randomChoice2 = gold;//(rand() % 26) + 1;
	cardCost1 = getCost(g.hand[randomPlayer][randomChoice1]);
	cardCost2 = getCost(gold);
	handCountPre = g.handCount[randomPlayer];
	validate = remodelCard(&g, handPos, randomPlayer, randomChoice1, randomChoice2);
	
	if(validate ==0){
	   printf("hand count before %d\n", handCountPre);
	   printf("cost of choice1 = %d\n",cardCost1);
	   printf("cost of choice2 = %d\n",cardCost2);
	   printf("hand count after %d\n", g.handCount[randomPlayer]);
	   //assert(cardCost2 <= (cardCost1+2));
	}
	
	
  }
   
   printf("all test passed");

   return 0;
}