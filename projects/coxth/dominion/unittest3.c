/******************************
* unittest3.c 
* Thomas Cox
* endTurn - This program test the endTurn() function.
* 4/23/2015
******************************/

#include "dominion.h"
#include "interface.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>


int main(int argc, char** argv){
  struct gameState g;
  int i,j;
  srand(time(NULL));
  int randomPlayer;
  int randomCardNumber;
  int coinSum;
  //int randomHandCount;
  int randomDeckCount;

  int cardArrayPre[26];
  //int cardArrayPost[26];
  
  
  for(i = 0; i < 1; i++){
  
	  coinSum = 0;
	  randomDeckCount = (rand() % MAX_HAND) + 1;
	  
	  
	  g.numPlayers = 4;//(rand() % 5)+2;;//randomPlayer+1;
	  randomPlayer = 2;//(rand() % g.numPlayers);
	 
	  g.whoseTurn = randomPlayer;
	  g.deckCount[randomPlayer] = 300;//randomDeckCount;
	  g.handCount[randomPlayer] = 50;//(rand() % randomDeckCount);
	  
	  g.outpostPlayed = 0;
	  g.phase = 0;
      g.numActions = 1;
      g.coins = 0;
      g.numBuys = 1;
      g.playedCardCount = 0;
     
	  
	  for(j=0;j < g.deckCount[randomPlayer]; j++){
	    randomCardNumber = 25;//(rand() % 27);
		g.deck[randomPlayer][j] = randomCardNumber;
		cardArrayPre[randomCardNumber]++;
	  }
	  for(j = 0; j < g.handCount[randomPlayer]; j++){
	      randomCardNumber = 25;//(rand() % 27);
		  g.hand[randomPlayer][j] = randomCardNumber;
		  cardArrayPre[randomCardNumber]++;
	  }
	  endTurn(&g);  
	  
	  printf("number of players = %d.\n", g.numPlayers);
	  printf("randomDeckCount = %d.\n", g.deckCount[randomPlayer]);
	  printf("randomPlayer = %d.\n",randomPlayer);
	  printf("randomCardNumber = %d \n", randomCardNumber);
	  printf("randomHandCount = %d\n", g.handCount[randomPlayer]);
  }

	

   return 0;
}