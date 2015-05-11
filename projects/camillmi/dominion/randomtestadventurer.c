/* -----------------------------------------------------------------------
 * TESTING: actionAdventurer (random)
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

int main() {

    // number of tests to run
    int NUM_TESTS = 100;

    // seed the random number generator
    srand(time(NULL));

	// Setup game variables
    int seed = 1000;
    int numPlayers;
    int targetHandSize;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    struct gameState *G = malloc(sizeof(struct gameState));
    struct gameState *G_copy = malloc(sizeof(struct gameState));

    // pick a random player
    // int currPlayer = rand() % numPlayers;
    int currPlayer;

    // add adventurer to player's hand at random location
    // int cardLoc = rand() % G->handCount[currPlayer];
    int cardLoc;

    // some variables to work with
    int i = 0;
    int j = 0;
    int treasures_o = 0;
    int treasures_n = 0;

    // start the random tests
    printf ("TESTING actionAdventurer (random):\n");
    for (j = 0; j < NUM_TESTS; j++)
    {
        numPlayers = rand() % 3 + 2; // random number of players (2-4)
        targetHandSize = rand() % 10 + 5; // random hand size > 5

        // pick a random player
        currPlayer = rand() % numPlayers;

        // use the random game variables to initialize the game
        initializeGame(numPlayers, k, seed, G);

        // set the turn
        G->whoseTurn = currPlayer;

        // draw hand to target hand size
        for(i = G->handCount[currPlayer]; i < targetHandSize; i++)
        {
            drawCard(G->whoseTurn, G);
        }

        // add adventurer to player's hand at random location
        // int cardLoc = rand() % G->handCount[currPlayer];
        cardLoc = 0;
        G->hand[currPlayer][cardLoc] = adventurer;

        // make a copy of the game state 
        memcpy(G_copy, G, sizeof(struct gameState));

        // run the function
        actionAdventurer(cardLoc, currPlayer, G);

        // Check size of hand is + 2 -1 for discard
        if (G->handCount[currPlayer] == G_copy->handCount[currPlayer] + 1)
        {
            printf("%d: actionAdventurer(): passed for hand count.\n", j);
        }
        else
        {
            printf("%d: actionAdventurer(): failed for hand count\n", j);
        }
        printf("   Exp: %d. Got: %d.\n", G_copy->handCount[currPlayer] + 1, G->handCount[currPlayer]);

        // Check number of treasures in hand is + 2
        treasures_o = 0;
        treasures_n = 0;
        for (i = 0; i < G_copy->handCount[currPlayer]; i++)
        {
            if ( G_copy->hand[currPlayer][i] == gold || G_copy->hand[currPlayer][i] == silver || G_copy->hand[currPlayer][i] == copper )
            {
                treasures_o++;
            }
        }
        for (i = 0; i < G->handCount[currPlayer]; i++)
        {
            if ( G->hand[currPlayer][i] == gold || G->hand[currPlayer][i] == silver || G->hand[currPlayer][i] == copper )
            {
                treasures_n++;
            }
        }
        if (treasures_n == treasures_o + 2)
        {
            printf("%d: actionAdventurer(): passed for treasure count\n", j);
        }
        else
        {
            printf("%d: actionAdventurer(): failed for treasure count\n", j);
        }
        printf("   Exp: %d. Got: %d.\n", treasures_o + 2, treasures_n);

        // Check that (-) change in size of deck = (+) change in size of hand + (+)
        // change in size of discard pile.

        if ( (G_copy->deckCount[currPlayer] - G->deckCount[currPlayer]) == 
             (G->handCount[currPlayer] - G_copy->handCount[currPlayer]) + 
             (G->discardCount[currPlayer] - G_copy->discardCount[currPlayer]) )
        {
            printf("%d: actionAdventurer(): passed for deck/hand/discard counts\n", j);
        }
        else
        {
            printf("%d: actionAdventurer(): failed for deck/hand/discard counts\n", j);
        }
    }

    exit(0);
}









