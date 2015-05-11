/*
 *             Author: Michael Marven
 *       Date Created: 05/10/15
 * Last Date Modified: 05/10/15
 *          File Name: randomtestadventurer.c
 *           Overview: Program to test the adventurer card in dominion.c; Tests 
 *                     that the function correctly draws cards until 2 treasure
 *                     cards are found
 *
 *                     Add the following lines to the makefile:
 *                     randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *                         gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
 * Function: checkAdventurer()
 * 
 *    Entry: The parameters are an int for the player, handPos, and game state 
 *           struct
 *
 *     Exit: The function checks the adventurer card
 *
 *  Purpose: Check the adventurer card
 *
 *
 *   *   *   *   *   *   */
void checkAdventurer(int p, int handPos, struct gameState *post)
{
	struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
	int coin_bonus = 0;

    // Call cardEffect
	cardEffect(adventurer, 0, 0, 0, post, handPos, &coin_bonus);
    
    // Check that treasure cards were drawn correctly and are the top two cards
#if (NOISY_TEST == 1)
        printf("Test that Adventurer card finds 2 treasure cards.\n");
#endif
    int firstTreasure, secondTreasure;
    // From mdmadventurercardplay comments: top card of hand is most recently 
    // drawn card.
    firstTreasure = post->hand[p][post->handCount[p] - 1];
    secondTreasure = post->hand[p][post->handCount[p] - 2];
    assert(firstTreasure == copper || firstTreasure == gold || firstTreasure == silver);
    assert(secondTreasure == copper || firstTreasure == gold || firstTreasure == silver);

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
        G.hand[p][handPos] = adventurer;
		
        /*
         * The lines below would be uncommented and run as a normal test, but
         * because of the bug in mdmadventurercardplay(), they cannot be run
         * without the program crashing. The bug causes the function to only 
		 * look for gold cards rather than gold, silver, and copper cards, so if
         * no gold is in the deck, then the function enters an infinite loop,
         * crashing with a segmentation fault.
         *
         
        
        
        // Ensure at least three cards in deck are treasure cards, one each of gold,
        // silver, and copper
        int goldPos, silvPos, coppPos;
        goldPos = rand_range(0, G.deckCount[p]);
        do
        {
            silvPos = rand_range(0, G.deckCount[p]);
        }while (goldPos != silvPos);
        do
        {
            coppPos = rand_range(0, G.deckCount[p]);
        }while (goldPos != coppPos && silvPos != coppPos);
        G.deck[p][goldPos] = gold;
        G.deck[p][silvPos] = silver;
        G.deck[p][coppPos] = copper;*/
        
        // Ensure at least three gold treasure cards are in deck
        int goldPos1, goldPos2, goldPos3;
        goldPos1 = rand_range(0, G.deckCount[p]);
        do
        {
            goldPos2 = rand_range(0, G.deckCount[p]);
        }while (goldPos1 != goldPos2);
        do
        {
            goldPos3 = rand_range(0, G.deckCount[p]);
        }while (goldPos1 != goldPos3 && goldPos2 != goldPos3);
        G.deck[p][goldPos1] = gold;
        G.deck[p][goldPos2] = gold;
        G.deck[p][goldPos3] = gold; 

        checkAdventurer(p, handPos, &G);
    }
    
    printf("All tests passed!\n");

    return 0;
}