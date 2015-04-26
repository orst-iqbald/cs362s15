/* -----------------------------------------------------------------------
 * Testing the outpost card in dominion.
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    int numOutpostsPlayed = 0;
    int failed = 0;

    //Taken from the example:
    printf ("TESTING Outpost Card:\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.hand[whoseTurn(&G)][0] = outpost; //Place aventurer into the hand
    numCards = G.handCount[whoseTurn(&G)]; //Get num cards
    numOutpostsPlayed = G.outpostPlayed; //Get num outposts played

    outpostEffect(&G, whoseTurn(&G), 0); //Play the outpost card

    //Make sure the hand = -1 card
    if(numCards == G.handCount[whoseTurn(&G)] + 1) {
        printf("Number of cards...PASSED\n");
    }
    else {
        printf("Number of cards...FAILED\n");
        failed++;
    }

    //Make sure that the number of outposts played increased
    if(numOutpostsPlayed == G.outpostPlayed + 1) {
        printf("Number of outposts...PASSED\n");
    }
    else {
        printf("Number of outposts...FAILED\n");
        failed++;
    }
    
    if(failed == 0) {
        printf("All tests passed!\n");
    }
    else {
        printf("Not all tests passed!\n");
    }
    
	return 0;
}