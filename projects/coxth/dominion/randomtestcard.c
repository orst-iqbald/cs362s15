/******************************
* randomtestcard.c
* Thomas Cox
* random smithy test - The smithy card draws three cards and the player who uses the
*				smithy card should have three more cards in their hand after the card is played
				if count occurs before the smith card is discarded.*
* 5/4/2015
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
  int seedTracker = 0;
  int numberOfPlayers = 0;
  int handPosition = 0;
  
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
  
  cardPlays = 300;

  for(i = 0; i < cardPlays; i ++){
	handPosition = 0; 
	seedTracker = 0;
	seed = (rand() % 65535);
	numberOfPlayers = ((rand() % 3) + 2);
    initializeGame(numberOfPlayers,k,seed,&g);
  
    treasureCardsPre = 0;
    treasureCardsPost = 0;
    handCountPre = 0;
    handCountPost = 0;
    randomPlayer = ((rand() % numberOfPlayers));
	
	printf("Number of players = %d\n", numberOfPlayers);
	printf("Random player drawn for = %d\n", randomPlayer);
	//printf("hand count of player = %d\n",g.handCount[randomPlayer]);  had a print statement here to make sure cards in hand was the right amount
    for(j = 0; j < g.handCount[randomPlayer];j++){
		if(g.hand[randomPlayer][j] == copper || g.hand[randomPlayer][j] == silver || g.hand[randomPlayer][j] == gold){
		  treasureCardsPre++; 
		} else {
			handPosition = j;
		}
		handCountPre = j + 1;
	}
    
  
  printf("treasure cards pre = %d\n",  treasureCardsPre);
  printf("cards in hand pre = %d\n", handCountPre);
  smithyCard(&g, handPosition, randomPlayer);
 
    for(j = 0; j < g.handCount[randomPlayer];j++){
		if(g.hand[randomPlayer][j] == copper || g.hand[randomPlayer][j] == silver || g.hand[randomPlayer][j] == gold){
		  treasureCardsPost++; 
		  handCountPost = j + 1;
		}
		
	}
   
   printf("treasure cards post = %d\n",  treasureCardsPost);
   printf("cards in hand post = %d\n", handCountPost);
   printf("hand position of smithy card = %d\n", handPosition);
   if((treasureCardsPre) > treasureCardsPost){
	   printf("Error on Smithy Card: Treasure cards pre: %d Treasure Cards post: %d\n", treasureCardsPre,treasureCardsPost);
	   seedTracker++;
	   printf("Game seed = %d\n", seed);
   }
   if((handCountPre +3) != handCountPost){
	   printf("Error on Smithy Card: Hand cards pre: %d Hand Cards post: %d\n", handCountPre,handCountPost);
	   if(seedTracker == 0){
		   printf("Game seed = %d\n", seed);
	   }
   }
   printf("---------------------------\n");
   
  }
   
  

   return 0;
}

