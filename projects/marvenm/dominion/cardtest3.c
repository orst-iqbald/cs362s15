/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: cardtest3.c
 *           Overview: Program to test the village card in dominion.c; Tests 
 *                     that 1 card is added to the hand and the actions increase
 *                     by 2
 *
 *                     Add the following lines to the makefile:
 *                     cardtest3: cardtest3.c dominion.o rngs.o
 *                         gcc -o cardtest3 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

static const int NUM_OF_TESTS = 1;

int main(int argc, char *argv[]) 
{
    // Seed the random number generator for the rand_range function
    srand(time(NULL));
    
    // Declare variables needed for test
    int r, t;
    int handCount;
    int actionCount;
    int calculatedHandCount;
    int calculatedActionCount;
	int topCard;
	int discardCount;
    int player     = 0;
    int coin_bonus = 0;
    int handPos    = 0;
    int numPlayers = 2;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("TESTING village card:\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d\n", t);
        
        // Clear the game state
        memset(&G, 0, sizeof(struct gameState));
        
        // Initialize game state
        r = initializeGame(numPlayers, k, seed, &G);
        
        // Retrieve the current hand count for player 1 and actions
        handCount = G.handCount[player];
        actionCount = G.numActions;
        
        // Change the card at handPos to a village card
        G.hand[player][handPos] = village;
            
#if (NOISY_TEST == 1)
        printf("Test that Village card adds 1 card to hand.\n");
#endif
        cardEffect(village, 0, 0, 0, &G, handPos, &coin_bonus);
        
        // Calculated hand count should be original + 1 - 1 for Village discard
        calculatedHandCount = handCount;

#if (NOISY_TEST == 1)
        printf("Player %d hand count = %d, expected %d.\n", player, 
                G.handCount[player], calculatedHandCount);
#endif
        assert(G.handCount[player] == calculatedHandCount);
        
#if (NOISY_TEST == 1)
        printf("Test that Village card adds 2 actions.\n");
#endif
        // Calculated action count should be original + 2
        calculatedActionCount = actionCount + 2;
        
#if (NOISY_TEST == 1)
        printf("Player %d action count = %d, expected %d.\n", player, 
                G.numActions, calculatedActionCount);
#endif
        assert(G.numActions == calculatedActionCount);
		
#if (NOISY_TEST == 1)
        printf("Test that Village card was discarded properly.\n");
#endif
        // If village card was discarded it would be on top of played card pile
		discardCount = G.playedCardCount;
        topCard = G.playedCards[discardCount - 1];
        
#if (NOISY_TEST == 1)
        printf("Player %d top discard = %d, expected %d.\n", 
                player, topCard, village);
#endif
        assert(topCard == village);
        
    }
    
    printf("All tests passed!\n");

    return 0;
}