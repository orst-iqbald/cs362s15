/*
 * Darnel Clayton
 * randomtestcard.c
 * Description: Random tester of smithy card from Dominion.c.
 * Originally referenced testUpdateCoins.c example.
 * CS362
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int checkSmithyCard(int p, struct gameState *G, int j) {
    struct gameState G2;
    memcpy (&G2, G, sizeof(struct gameState));

    int handCount = G2.handCount[p];
    int playedCardCount = G2.playedCardCount;

    smithyCard(j, p, &G2);
	// Compare with expected results with every initialization of the gamestate.
    printf("Cards in hand = %d, expected cards in hand = %d\n", G2.handCount[p], handCount + 2);
    printf("Cards in play = %d, expected cards in play = %d\n", G2.playedCardCount, playedCardCount + 1);
    assert(G.playedCardCount == playedCardCount + 1);

    return 0;
}

int main() {

    srand(time(NULL));


   // Random game parameters
    int seed = floor((rand() * 1200) + 1);
    int numPlayer = floor((rand() % 3) + 2); // Selecting random number of players.
                                             // Selects 0,1, or 2. Then add 2. (# of players 2-4.)
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    int i,p,r,j;

    initializeGame(numPlayer, k, seed, &G); // initialize a new game.
    int numCards=15;//Control loop.

    //Taken from the example:
    printf ("RANDOM TESTING Smithy Card:\n");

    for (i = 0; i < numcards; i++) {
   	memset(&G, 23, sizeof(struct gameState));   // clear the game state
   	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);
        j = floor(Random() * G.handCount[p]);
        G.hand[p][j] = smithy; 
        checkSmithyCard(p, &G, j);
    }
printf("RANDOM TEST OF SMITHY CARD COMPLETED.");
/*
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
*/
	return 0;
}
