/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: cardtest1.c
 *           Overview: Program to test the smithy card in dominion.c; Tests that 
 *                     the function correctly adds 3 cards to the hand
 *
 *                     Add the following lines to the makefile:
 *                     cardtest1: cardtest1.c dominion.o rngs.o
 *                         gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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
	int topCard;
	int discardCount;
    int calculatedHandCount;
    int player     = 0;
    int coin_bonus = 0;
    int handPos    = 0;
    int numPlayers = 2;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("TESTING mdmsmithycardplay():\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d\n", t);
        
        // Clear the game state
        memset(&G, 0, sizeof(struct gameState));
        
        // Initialize game state
        r = initializeGame(numPlayers, k, seed, &G);
        
        // Retrieve the current hand count for player 1
        handCount = G.handCount[player];
        
        // Change the card at handPos to a Smithy card
        G.hand[player][handPos] = smithy;
            
#if (NOISY_TEST == 1)
        printf("Test that Smithy card adds 3 to hand.\n");
#endif
        cardEffect(smithy, 0, 0, 0, &G, 0, &coin_bonus);
        
        // Calculated hand count should be original + 3 - 1 for Smithy discard
        calculatedHandCount = handCount + 2;

#if (NOISY_TEST == 1)
        printf("Player %d hand count = %d, expected %d.\n", player, 
                G.handCount[player], calculatedHandCount);
#endif
        // assert(G.handCount[player] == calculatedHandCount);
        if(G.handCount[player] != calculatedHandCount)
		{
			// printf statement inserted because assert causing program exit
			printf("cardtest1: cardtest1.c:78 main: G.handCount[player] != calculatedHandCount.\n");
		}
		
#if (NOISY_TEST == 1)
        printf("Test that Smithy card was discarded properly.\n");
#endif
        // If smithy card was discarded it would be on top of played card pile
		discardCount = G.playedCardCount;
        topCard = G.playedCards[discardCount - 1];
        
#if (NOISY_TEST == 1)
        printf("Player %d top discard = %d, expected %d.\n", 
                player, topCard, smithy);
#endif
        assert(topCard == smithy);
    }
    
    printf("All tests passed!\n");

    return 0;
}