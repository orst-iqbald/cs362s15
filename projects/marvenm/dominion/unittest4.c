/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: unittest4.c
 *           Overview: Program to test numHandCards() in dominion.c; Tests that 
 *                     the function correctly returns the hand count of the
 *                     current player
 *
 *                     Add the following lines to the makefile:
 *                     unittest4: unittest4.c dominion.o rngs.o
 *                         gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
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

static const int NUM_OF_TESTS = 5;

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
    int r, t;
    int randPlayer;
    int randHandCount;
    int returnedCount;
    int numPlayers = 4;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("TESTING numHandCards():\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d\n", t);
        
        // Clear the game state
        memset(&G, 0, sizeof(struct gameState));
        
        // Initialize game state
        r = initializeGame(numPlayers, k, seed, &G);
        
        // Randomly set whose turn it is
        randPlayer = rand_range(1, 4);
        
        // Randomly set the hand count for that player
        randHandCount = rand_range(1, MAX_HAND);
            
#if (NOISY_TEST == 1)
        printf("Test number of hand cards for player %d.\n", randPlayer);
#endif
        G.handCount[randPlayer] = randHandCount;
        G.whoseTurn = randPlayer;
        
        returnedCount = numHandCards(&G);

#if (NOISY_TEST == 1)
        printf("Player %d hand count = %d, expected %d.\n", randPlayer, 
                returnedCount, randHandCount);
#endif
        assert(returnedCount == randHandCount);
        
    }
    
    printf("All tests passed!\n");

    return 0;
}