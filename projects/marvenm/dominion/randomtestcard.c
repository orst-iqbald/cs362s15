/*
 *             Author: Michael Marven
 *       Date Created: 05/10/15
 * Last Date Modified: 05/10/15
 *          File Name: randomtestcard.c
 *           Overview: Program to test the salvager card in dominion.c; 
 *
 *                     Add the following lines to the makefile:
 *                     randomtestcard: randomtestcard.c dominion.o rngs.o
 *                         gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
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

/*   *   *   *   *   *   *
 * 
 * Function: rand_range()
 * 
 *    Entry: The parameters are ints for the minimum and maximum range values
 *
 *     Exit: The function returns an int in the range, inclusive of the stated
 *           limits
 *
 *  Purpose: The function generates a number within a range without some 
 *           numbers generating more than others and output skewing toward those
 *           values; More information available at the link below;
 *           Adapted from the Stack Overflow answer located at:
 *           http://stackoverflow.com/questions/2999075/generate-a-random-
 *           number-within-range/2999130#2999130
 *
 *
 *   *   *   *   *   *   */
int rand_range(int min, int max)
{
    // Generate a divisor for the rand() function
    int divisor = RAND_MAX / ((max - min) + 1);
    int output;

    do
    {
        output = rand() / divisor;
    }while (output > (max - min));

    return (output + min);
}

/*   *   *   *   *   *   *
 * 
 * Function: checkSalvager()
 * 
 *    Entry: The parameters are an int for the player and game state struct
 *
 *     Exit: The function checks the salvager card
 *
 *  Purpose: Check the salvager card
 *
 *
 *   *   *   *   *   *   */
void checkSalvager(int p, int handPos, struct gameState *post)
{
	struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
	int coin_bonus = 0;
    int randChoice;
    int randCost;
    int randCard;
    
    // Pick a random card to discard and get the cost of that card
    randChoice = rand_range(1, pre.handCount[p]);
    randCost = getCost( handCard(randChoice, &pre) );
    randCard = handCard(randChoice, &pre);
    
    // Call cardEffect
	cardEffect(salvager, randChoice, 0, 0, post, handPos, &coin_bonus);
    
    // Check that buys and coins were increased correctly and cards were 
    // discarded and trashed correctly
#if (NOISY_TEST == 1)
        printf("Test that Salvager card adds 1 buy and adds coins equal to\n");
        printf("the card that is trashed.\n");
#endif

    
    if(post->numBuys != pre.numBuys + 1)
    {
        printf("Error: Buys not incremented by 1.\n");
    }
    
    if(post->coins != pre.coins + randCost)
    {
        printf("Error: Coins not incremented by %d.\n", randCost);
    }
    
    if(post->playedCards[post->playedCardCount - 1] != salvager)
    {
        printf("Error: Salvager card not discarded properly.\n");
    }
    
    if(post->playedCards[post->playedCardCount - 2] == randCard)
    {
        printf("Error: Trashed card discarded rather than trashed.\n");
    }

}

int main(int argc, char *argv[]) 
{
    // Seed the random number generator for the rand_range function
    srand(time(NULL));
    
    // Declare variables needed for test
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r;
	int handPos = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("Testing Adventurer card - random:\n");
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    int n;
    for (n = 0; n < 10; n++)
    {
        printf("Starting test %d\n", n);
        
		// Set player to 0
        p = 0;
        
        // Set counts to random values
        G.deckCount[p] = rand_range(3, MAX_DECK); // Ensures deck has at least 3 cards
        G.discardCount[p] = rand_range(0, MAX_DECK);
        G.handCount[p] = rand_range(0, MAX_HAND);
        
        // Fill player's hand with random cards
        for (i = 0; i < G.handCount[p]; i++)
        {
            G.hand[p][i] = rand_range(0, 26);
        }
        
        // Fill player's deck with random cards
        for (i = 0; i < G.deckCount[p]; i++)
        {
            G.deck[p][i] = rand_range(0, 26);
        }
        
        // Fill player's discard pile with random cards
        for (i = 0; i < G.discardCount[p]; i++)
        {
            G.discard[p][i] = rand_range(0, 26);
        }
        
		// Change the card at handPos to an Adventurer card
        G.hand[p][handPos] = salvager;
		 

        checkSalvager(p, handPos, &G);
    }
    
    printf("All tests passed!\n");

    return 0;
}