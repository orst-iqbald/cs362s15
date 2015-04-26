/* *****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four Dominion cards implemented in dominion.c. These tests 
should be checked in as cardtest1.c, cardtest2.c,cardtest3.c, and cardtest4.c. 
(For example, create a test for smithy card.). 
It is mandatory to test smithy and adventurer card. 

test of great_hall
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int testGreat_Hall(int handPos, int player, struct gameState *post) {
	int currPlayer = player;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int card = great_hall;
	int r = cardEffect(card, 0, 0, 0, &pre, handPos, 0);
	
	// draw a card
	drawCard(currPlayer, post);

	// add an action
	post->numActions++;

	// discard card from hand
	discardCard(handPos, currPlayer, post, 0);
	
	//Check that pre and post gameStates are equivalent
	assert (r == 0);
	assert (pre.numBuys == post->numBuys);
	assert (pre.discardCount[pre.whoseTurn] == post->discardCount[pre.whoseTurn]);
	assert (pre.handCount[pre.whoseTurn] == post->handCount[pre.whoseTurn]);
	assert (pre.deckCount[currPlayer] == post->deckCount[currPlayer]);
	return 0;
}

int main() {
	struct gameState G;
	int player;
	int i;
	int pos;

	printf("Testing great_hall....\n");

   // Initialize the gameState with random bytes
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 255);
    }

    G.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
    player = floor(Random() * G.numPlayers);
    G.whoseTurn = player;

    //Set deck/hand/discard values to reasonable numbers
    for (i = 0; i < G.numPlayers; i++) {
      G.deckCount[i] = floor(Random() * (MAX_DECK));
      G.handCount[i] = floor(Random() * (MAX_DECK - 4));
      G.discardCount[i] = floor(Random() * (MAX_DECK));
    }

    G.playedCardCount = floor(Random() * MAX_DECK);
    G.numBuys = 1;//floor(Random() * 10);
    
    //Set position to within range of handCount[]
    pos = floor(Random() * (G.handCount[player]));
 
 	// testing great_hall
	testGreat_Hall(pos, player, &G);
    printf("great_hall Passes...\n");
    return 0;
}
