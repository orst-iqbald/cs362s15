/******************************
* cardtest1.c 
* Thomas Cox
* adventurer test - reveal cards from your deck until you reveal 2 treasure cards.
                    Put those Treasure cards into your hand and discard the other revealed cards.
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
  int i,j;
  srand(time(NULL));
  int cardPlays;
  int seed = 0;
  int treasureCardsPre = 0;
  int treasureCardsPost = 0;
  int handCountPre = 0;
  int handCountPost = 0;
  int randomPlayer;
  
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
  
  cardPlays = 5;
  seed = (rand() % 65535);
  
  
  initializeGame(4,k,seed,&g);
  

  for(i = 0; i < cardPlays; i ++){
    treasureCardsPre = 0;
    treasureCardsPost = 0;
    handCountPre = 0;
    handCountPost = 0;
    randomPlayer = (rand() % 4);
	printf("random player = %d\n", randomPlayer);
	
    for(j = 0; j < g.handCount[randomPlayer];j++){
		if(g.hand[randomPlayer][j] == copper || g.hand[randomPlayer][j] == silver || g.hand[randomPlayer][j] == gold){
		  treasureCardsPre++; 
		  handCountPre = j + 1;
		}
	}
 
  printf("treasure cards pre = %d\n",  treasureCardsPre);
  printf("cards in hand pre = %d\n", handCountPre);
  adventurerCard(&g,0, randomPlayer);
 
    for(j = 0; j < g.handCount[randomPlayer];j++){
		if(g.hand[randomPlayer][j] == copper || g.hand[randomPlayer][j] == silver || g.hand[randomPlayer][j] == gold){
		  treasureCardsPost++; 
		  handCountPost = j + 1;
		}
	}
   printf("treasure cards post = %d\n",  treasureCardsPost);
   printf("cards in hand post = %d\n", handCountPost);
   assert((treasureCardsPre + 2) == treasureCardsPost);
   assert((handCountPre + 2) == handCountPost);
  }
   
   printf("all test passed");

   return 0;
}