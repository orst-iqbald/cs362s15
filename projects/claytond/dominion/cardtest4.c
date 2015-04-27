/*
Darnel Clayton
cardtest4.c
Testing smithy card from Dominion.c
Referenced testUpdateCoins.c example.
CS 362
*/


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

    //Taken from the example:
    printf ("TESTING Smithy Card:\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.hand[whoseTurn(&G)][0] = smithy; //Place a smithy card into the player's hand
	numCards = G.handCount[whoseTurn(&G)]; //Get the number of cards in the player's hand 

	smithyEffect(&G, whoseTurn(&G), 0);

	//Make sure that hand now has 2 more cards (Assuming you discarded smithy, 3-1=2)
	if(G.handCount[whoseTurn(&G)] == numCards + 2) {
		printf("Hand has the proper number of cards, smithy test PASSED.\n");
	}
	else {
		printf("Hand did not have the proper number of cards, smithy test FAILED.\n");
	}

	return 0;
}
