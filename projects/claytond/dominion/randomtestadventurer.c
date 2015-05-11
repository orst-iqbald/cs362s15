/*
 * Darnel Clayton
 * randomtestadventurer.c
 * Description: Random tester of adventurer card from Dominion.c.
 * Originally referenced testUpdateCoins.c example.
 * CS362
 */

#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <assert.h>

int checkAdventurerCard(int p, struct gameState *G) {
    struct gameState G2;
    memcpy (&G2, G, sizeof(struct gameState));
    
    int handCount = G2.handCount[p];
    printf("Initial cards in hand: %d\n", handCount);

    adventurerCard(p, &G2);

    // Compare with expected results with every initialization of the gamestate.
    printf("Current cards in hand = %d, expected cards in hand = %d\n", G2.handCount[p], handCount + 2);

    return 0;
}

int main(void) {
	
    srand(time(NULL));

 
   // Randome game parameters
    int seed = floor((Random() * 1200) + 1);
    int numPlayer = floor((rand() % 3) + 2); // Selecting random number of players. 
					     // Selects 0,1, or 2. Then add 2. (# of players 2-4.)
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    int i,p;

    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf ("RANDOM TESTING adventurerCard():\n");

    for (i = 0; i < testIterations; i++) {
        G.deckCount[p] = floor(Random() * MAX_DECK);
        // fill deck with random cards
        for(n = 0; n < G.deckCount[p]; n++) {
            G.deck[p][n] = floor(rand() * 26 + 1);
        }
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);
        checkAdventurerCard(p, &G);
    }

/*
//Encapsulated functionality into checkAdventurerCard function.
//Values to be checked with every iteration and random initialization of the gamestate.
    printf("Cards in hand = %d, expected cards in hand = %d\n", G.handCount[1], 5);
    assert(G.handCount[1] == 5);
    adventurerCard(1, &G);
    printf("Cards in hand = %d, expected cards in hand = %d\n", G.handCount[1], 6);
*/
    return 0;
}
