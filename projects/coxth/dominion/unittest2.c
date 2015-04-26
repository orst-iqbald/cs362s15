/******************************
* unittest2.c 
* Thomas Cox
* shuffle - This program test the shuffle function.
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
  int randomDeckCount;
  
  int cardArrayPre[26];
  int cardArrayPost[26];
  
  
  
  for(i = 0; i < 5; i++){
  
	  coinSum = 0;
	  randomDeckCount = (rand() % MAX_HAND) + 1;
	  randomPlayer = (rand() % 6);
	  for(j = 0; j < 27; j++){
	    cardArrayPre[j] = 0;
		cardArrayPost[j] = 0;
	  }
	  
	  
	  g.deckCount[randomPlayer] = randomDeckCount;
	  
	  for(j = 0; j < randomDeckCount; j++){
	      randomCardNumber = (rand() % 27);
		  cardArrayPre[randomCardNumber]++;
		  g.deck[randomPlayer][j] = randomCardNumber;
	  }
	  
	  shuffle(randomPlayer, &g);
	  
	  for(j = 0; j < randomDeckCount; j++){
		  cardArrayPost[g.deck[randomPlayer][j]]++;
	  }
	  
	  for(j = 0; j < 27; j++){
	    printf("Pre = %d Post = %d \n",cardArrayPre[j],cardArrayPost[j]);
		if(cardArrayPre[j] != cardArrayPost[j]){
		  printf("error pre and post card count after shuffle are not the same");
		}
	  }
	  printf("\n\n");
	  
	  printf("randomDeckCount = %d.\n", randomDeckCount);
	  printf("randomPlayer = %d.\n",randomPlayer);
	  printf("randomCardNumber = %d \n", randomCardNumber);
  
	  //there is an occasional variance in the quantity of each card when the deck gets shuffled
	 //gcc unittest2.c -m -o unittest2
	 // assert(g.coins == coinSum);
  }
   return 0;
}