/* ***************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 4
randomtestadventurer.c

Write a random testers for two Dominion cards, one of which has to be the 
adventurer card. Check these random testers in as randomtestcard.c and 
randomtestadventurer.c.

random test for adventurer card

"make randomadventurertest"
*************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int checkAdventurer(int card, struct gameState *post, int handPos) 
{
  struct gameState pre;
  
	//printf("copying hand state\n");
  memcpy (&pre, post, sizeof(struct gameState));

  //printf(" sending i copy to the main card code\n");
	int r;
  r = cardEffect(card, 0, 0, 0, post, handPos, 0);
  
	//printf(" duplicating code effects\n");
  int treasure = 0;
  int newcard;
  int z = 0;
  int temp[MAX_HAND];
  int currPlayer = whoseTurn(&pre);
	
	//printf(" draw cards\n");
  // draw cards until 2 treasures cards are drawn; discard the other cards
  while (treasure < 2) {
    if(pre.deckCount[currPlayer]<1){
      shuffle(currPlayer, &pre);
    }
    drawCard(currPlayer, &pre);
    newcard = pre.hand[currPlayer][(pre.handCount[currPlayer])-1];
    if (newcard == copper || newcard == silver || newcard == gold) {
      treasure++;
    } 
    else {
      temp[z] = newcard;
      pre.handCount[currPlayer]--;
      z++;
    }
  }
  while (z-1>=0){
    pre.discard[currPlayer][pre.discardCount[currPlayer]++] = temp[z-1];
    z=z-1;
  }
  
  assert (r == 0); // indicates the card played true
	
	//Check that pre and post gameStates are equivalent
 	assert (pre.numBuys == post->numBuys);
	assert (pre.discardCount[pre.whoseTurn] == post->discardCount[pre.whoseTurn]);
	assert (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn]);
	assert (pre.deckCount[currPlayer] == post->deckCount[currPlayer]);
 	assert (memcmp(&pre, post, sizeof(struct gameState)) == 0);
  
	return 0;
}

int main () 
{
  int i, n, pos, player, r;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Random Testing Adventurer.\n");

  SelectStream(2);
  PutSeed(3);
  //printf(" going into init \n");
  // Initialize the gameState with random bytes

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }

	  r = initializeGame(2, k, 1, &G);
    G.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
    player = floor(Random() * G.numPlayers);
    G.whoseTurn = player;

	  //printf(" setting deck\n");
    //Set deck/hand/discard values to reasonable numbers
    for (i = 0; i < G.numPlayers; i++) {
      G.deckCount[i] = floor(Random() * (MAX_DECK));
      G.handCount[i] = floor(Random() * (MAX_DECK - 4));
      G.discardCount[i] = floor(Random() * (MAX_DECK));
    }

    G.playedCardCount = floor(Random() * MAX_DECK);
    G.numBuys = 1;
    
    //printf(" setting handpos\n");
    //Set position to within range of handCount[]
    pos = floor(Random() * (G.handCount[player]));
   
		//printf(" checking card\n");
    //Test adventurer function
    checkAdventurer(adventurer, &G, pos);
  	printf ("adventurer passes...\n");
	}
	return 0;
}

