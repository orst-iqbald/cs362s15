/* -----------------------------------------------------------------------
 * Testing the adventurer card in dominion.
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    int numCards = 0;
    int newNumCards = 0;

    //Taken from the example:
    printf ("TESTING Adventurer Card:\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.hand[whoseTurn(&G)][0] = adventurer; //Place aventurer into the hand

    //Go through the beginning of the hand and see how many treasure cards there are
    int i;
    for(i = 0; i < G.handCount[whoseTurn(&G)]; i++) {
    	if(G.hand[whoseTurn(&G)][i] == copper || G.hand[whoseTurn(&G)][i] == silver || G.hand[whoseTurn(&G)][i] == gold) {
    		numCards++;
    	}
    }

    //printf("%d", numCards);

    adventurerEffect(&G, whoseTurn(&G)); //Run adventurer card

    //Now go through hand and make sure there are 2 more treasure cards in it
    for(i = 0; i < G.handCount[whoseTurn(&G)]; i++) {
    	if(G.hand[whoseTurn(&G)][i] == copper || G.hand[whoseTurn(&G)][i] == silver || G.hand[whoseTurn(&G)][i] == gold) {
    		newNumCards++;
    	}
    }

    //printf("%d", newNumCards);
    //printf("%d %d", numCards, newNumCards);

    if(newNumCards == numCards + 2) {
    	printf("Adventurer card test passed!\n");
    }
    else {
    	printf("Adventurer card test failed!\n");
    }

	return 0;
}