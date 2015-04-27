/* -----------------------------------------------------------------------
 * Testing the village card in dominion.
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int numCards;
    int numActions;

    //Taken from the example:
    printf ("TESTING Village Card:\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.hand[whoseTurn(&G)][0] = village; //Place village into the hand
    numCards = G.handCount[whoseTurn(&G)]; //Get num cards
    numActions = G.numActions; //Get num actions

    villageEffect(&G, whoseTurn(&G), 0); //Run the village card

	//Make sure that hand now has same num cards (Assuming you discarded smithy, 1-1=0)
	if(G.handCount[whoseTurn(&G)] == numCards) {
		printf("Hand has the proper number of cards, village card test PASSED.\n");
	}
	else {
		printf("Hand did not have the proper number of cards, village card test FAILED.\n");
	}

	//Make sure # of actions is good (2-1=1)
	if(G.numActions == numActions + 1) {
		printf("Hand has the proper number of actions, village action test PASSED.\n");
	}
	else {
		printf("Hand did not have the proper number of actions, village action test FAILED.\n");
	}

	return 0;
}