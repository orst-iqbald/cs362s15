/* *****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four Dominion cards implemented in dominion.c. These tests 
should be checked in as cardtest1.c, cardtest2.c,cardtest3.c, and cardtest4.c. 
(For example, create a test for smithy card.). 
It is mandatory to test smithy and adventurer card. 

test of council_room (refactored card)
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testCouncil_Room(int handPos, int player, struct gameState *post) {
	struct gameState pre;
	int currPlayer = player;
	memcpy(&pre, post, sizeof(struct gameState));
	int card = council_room;

	int r = cardEffect(card, 0, 0, 0, &pre, handPos, 0);
	// draw 4 cards
	int i;
	for (i = 0; i < 4; i++) {
		drawCard(currPlayer, post);
	}

	// add a "buy"
	post->numBuys++;

	// other players draw a card
	for (i = 0; i < post->numPlayers; i++) {
		if (i != currPlayer) {
			drawCard(i, post);
		}
	}

	// play card
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
  int i, pos, player;
  struct gameState G;

	printf("Testing council_room....\n");

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
 
     //Test council_room function
	testCouncil_Room(pos, player, &G);

	printf("Ending council_room test...\n");
	return 0;
}