/* -----------------------------------------------------------------------
 * Random testing the adventure card in dominion.
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define NUM_TESTS 1000

int main() {
    int r;
    int seed = 100;
    int numPlayer = 2;
    //int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int i;
    int j;
    int errors = 0;

    printf ("TESTING Adventurer Card:\n");
    
    srand(time(NULL)); //Seed the random num

    for(i = 0; i < NUM_TESTS; i++) {
        int beforeTreasure = 0;
        int afterTreasure = 0;
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

        //Pick a player at random
        G.whoseTurn = floor(rand() % MAX_PLAYERS + 1); //Choose a random player
        G.deckCount[whoseTurn(&G)] = floor(rand() % MAX_DECK + 1); //Put random num of cards in deck
        G.handCount[whoseTurn(&G)] = floor(rand() % MAX_HAND + 1); //Put random num of cards in hand
        G.discardCount[whoseTurn(&G)] = MAX_DECK - (G.deckCount[whoseTurn(&G)] + G.handCount[whoseTurn(&G)]); //Set the discarded num of cards to the remainder

        //Now that you have # of cards in each, put actual cards in them
        for(j = 0; j < G.deckCount[whoseTurn(&G)]; j++) {
            G.deck[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) {
            G.hand[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < G.discardCount[whoseTurn(&G)]; j++) {
            G.discard[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }

        //Now choose a random spot in the player's hand
        j = floor(rand() % G.handCount[whoseTurn(&G)] + 1);
        G.hand[whoseTurn(&G)][j] = adventurer;

        //Copy the game state
        //memcpy(&H, &G, sizeof(struct gameState));
        int totalNumCards = G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)];

        //Count # of treasure cards before
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) {
            if(G.hand[whoseTurn(&G)][j] == copper || G.hand[whoseTurn(&G)][j] == silver || G.hand[whoseTurn(&G)][j] == gold) {
                beforeTreasure++;
            }
        }

        adventurerEffect(&G, whoseTurn(&G)); //Run adventurer card

        //Count # of treasure cards after
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) {
            if(G.hand[whoseTurn(&G)][j] == copper || G.hand[whoseTurn(&G)][j] == silver || G.hand[whoseTurn(&G)][j] == gold) {
                afterTreasure++;
            }
        }

        //Start checking everything
        //Total # of cards
        if(G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)] != totalNumCards - 2) {
            printf("Test #%d-a FAILED. The total number of cards don't add up. %d vs %d\n", i, G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)], totalNumCards - 2);
            errors++;
        }

        //Check and make sure there are 2 more treasure cards
        if(afterTreasure != beforeTreasure + 2) {
            printf("Test #%d-b FAILED. The total number of teasure cards don't add up. %d vs %d\n", i, afterTreasure, beforeTreasure + 2);
            errors++;
        }

        if(errors == 0) {
            printf("Test #%d PASSED.\n\n", i);
        }
        else {
            printf("Test #%d FAILED.\n\n", i);
        }
    }

    return 0;
}