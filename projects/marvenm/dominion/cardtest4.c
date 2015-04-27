/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: cardtest4.c
 *           Overview: Program to test the salvager card in dominion.c; Tests 
 *                     that 1 buy is added, that coins equivalent to a trashed
 *                     card are added, the trashed card is actually trashed, and
 *                     the salvager card is discraded
 *
 *                     Add the following lines to the makefile:
 *                     cardtest4: cardtest4.c dominion.o rngs.o
 *                         gcc -o cardtest4 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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
    int discardCount;
    int buyCount;
    int calculatedBuyCount;
    int coinCount;
    int calculatedCoinCount;
    int topCard;
    int player     = 0;
    int coin_bonus = 0;
    int handPos    = 0;
    int choicePos  = 1;
    int numPlayers = 2;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("TESTING salvager card:\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d\n", t);
        
        // Clear the game state
        memset(&G, 0, sizeof(struct gameState));
        
        // Initialize game state
        r = initializeGame(numPlayers, k, seed, &G);
        
        // Retrieve the buys and coins
        buyCount = G.numBuys;
        coinCount = G.coins;
        
        // Change the card at handPos to a salvager card
        G.hand[player][handPos] = salvager;
        
        // Change the card at choicePos to gold
        G.hand[player][choicePos] = gold;
            
#if (NOISY_TEST == 1)
        printf("Test that Salvager card adds 1 buy.\n");
#endif
        cardEffect(salvager, choicePos, 0, 0, &G, handPos, &coin_bonus);
        
        // Calculated buy count should be original + 1
        calculatedBuyCount = buyCount + 1;

#if (NOISY_TEST == 1)
        printf("Player %d buy count = %d, expected %d.\n", player, 
                G.numBuys, calculatedBuyCount);
#endif
        assert(G.numBuys == calculatedBuyCount);
        
#if (NOISY_TEST == 1)
        printf("Test that coins are increased by the cost of gold (6).\n");
#endif
        // Calculated coin count should be original + 6 for cost of gold
        calculatedCoinCount = coinCount + 6;
        
#if (NOISY_TEST == 1)
        printf("Player %d coin count = %d, expected %d.\n", player, 
                G.coins, calculatedCoinCount);
#endif
        assert(G.coins == calculatedCoinCount);
        
#if (NOISY_TEST == 1)
        printf("Test that choice card is trashed and not discarded.\n");
#endif
        // If choice card was discarded playedCardCount would be 2
        discardCount = G.playedCardCount;
        
#if (NOISY_TEST == 1)
        printf("Player %d played card count = %d, should not be %d.\n", 
                player, discardCount, 2);
#endif
        assert(discardCount != 2);
        
#if (NOISY_TEST == 1)
        printf("Test that Salvager card was discarded properly.\n");
#endif
        // If salvager card was discarded it would be on top of played card pile
        topCard = G.playedCards[discardCount - 1];
        
#if (NOISY_TEST == 1)
        printf("Player %d top discard = %d, expected %d.\n", 
                player, topCard, salvager);
#endif
        assert(topCard == salvager);
        
    }
    
    printf("All tests passed!\n");

    return 0;
}