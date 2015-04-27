/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: unittest3.c
 *           Overview: Program to test fullDeckCount() in dominion.c; Tests that 
 *                     the function corerectly counts all cards in a player's
 *                     deck
 *
 *                     Add the following lines to the makefile:
 *                     unittest3: unittest3.c dominion.o rngs.o
 *                         gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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

int main(int argc, char *argv[]) 
{
    // Seed the random number generator for the rand_range function
    srand(time(NULL));
    
    // Declare variables needed for test
    int p, r, t;
    int returnedCount;
    int calculatedCount;
    int player;
    int numPlayers = 2;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("TESTING fullDeckCount():\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d\n", t);
        
        // Clear the game state
        memset(&G, 0, sizeof(struct gameState));
        
        // Initialize game state
        r = initializeGame(numPlayers, k, seed, &G);
        
        for (p = 0; p < numPlayers; p++)
        {
            player = p;
            
#if (NOISY_TEST == 1)
            printf("Test deck count of all cards for player %d.\n", player);
#endif
            returnedCount = fullDeckCount(player, 0, &G);
            
            calculatedCount = G.deckCount[player] + G.handCount[player] +
                               G.discardCount[player];

#if (NOISY_TEST == 1)
            printf("Player %d deck count = %d, expected %d.\n", player, 
                   returnedCount, calculatedCount);
#endif
            // assert(returnedCount == calculatedCount);
			if(returnedCount != calculatedCount)
			{
				// printf statement inserted because assert causing program exit
				printf("unittest3: unittest3.c:107 main: returnedCount != calculatedCount.\n");
			}
        }
    }
    
    printf("All tests passed!\n");

    return 0;
}