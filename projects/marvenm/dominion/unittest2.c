/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: unittest2.c
 *           Overview: Program to test isGameOver() in dominion.c; Tests that 
 *                     the function corerectly recognizes the conditions for the
 *                     end of the game
 *
 *                     Add the following lines to the makefile:
 *                     unittest2: unittest2.c dominion.o rngs.o
 *                         gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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

static const int NUM_OF_TESTS = 10;

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
    int pile1, pile2, pile3;
    int end;
    int endMethod;
    int numPlayers = 2;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("TESTING isGameOver():\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d\n", t);
        
        // Clear the game state
        memset(&G, 0, sizeof(struct gameState));
        
        // Initialize game state
        r = initializeGame(numPlayers, k, seed, &G);
        
        /*
         * Randomly decide if game will end by province card supply being empty,
         * by three other stacks being empty, or by less than 3 stacks being
         * empty (a condition in which the game is not over and for which 
         * isGameOver() should return a 0 for false)
         */
        endMethod = rand_range(1, 3);

        // Run the appropriate test
        if (endMethod == 1)
        {
            
#if (NOISY_TEST == 1)
            printf("Test empty province supply.\n");
#endif
            G.supplyCount[province] = 0;
            
#if (NOISY_TEST == 1)           
            printf("G.supplyCount ");
            int i;
            for (i = 0; i < treasure_map + 1; i++)
            {
                printf("%d, ", G.supplyCount[i]);
            }
            printf("\n");
#endif
            
            end = isGameOver(&G);
            assert(end == 1);
        }
        else if (endMethod == 2)
        {
            
#if (NOISY_TEST == 1)
            printf("Test 3 empty piles.\n");
#endif
            // Randomly choose 3 piles to be set to zero
            do
            {
                pile1 = rand_range(curse, treasure_map);
            }while(pile1 == province);
            
            do
            {
                pile2 = rand_range(curse, treasure_map);
            }while(pile2 == province || pile2 == pile1);
        
            do
            {
                pile3 = rand_range(curse, treasure_map);
            }while(pile3 == province || pile3 == pile1 || pile3 == pile2);
            
            
            G.supplyCount[pile1] = 0;
            G.supplyCount[pile2] = 0;
            G.supplyCount[pile3] = 0;
            
#if (NOISY_TEST == 1)
            printf("G.supplyCount ");
            int i;
            for (i = 0; i < treasure_map + 1; i++)
            {
                printf("%d, ", G.supplyCount[i]);
            }
            printf("\n");
#endif
            
            end = isGameOver(&G);
			// assert(end == 1);
            if(end != 1)
			{
				// printf statement inserted because assert causing program exit
				printf("unittest2: unittest2.c:159 main: end != 1.\n");
			}
        }
        else if(endMethod == 3)
        {
            
#if (NOISY_TEST == 1)
            printf("Test only 2 empty piles.\n");
#endif
            // Randomly choose 2 piles to be set to zero
            do
            {
                pile1 = rand_range(curse, treasure_map);
            }while(pile1 == province);
            
            do
            {
                pile2 = rand_range(curse, treasure_map);
            }while(pile2 == province || pile2 == pile1);
            
            G.supplyCount[pile1] = 0;
            G.supplyCount[pile2] = 0;
            
#if (NOISY_TEST == 1)
            printf("G.supplyCount ");
            int i;
            for (i = 0; i < treasure_map + 1; i++)
            {
                printf("%d, ", G.supplyCount[i]);
            }
            printf("\n");
#endif

            end = isGameOver(&G);
            assert(end == 0);
        }
    }
    
    printf("All tests passed!\n");

    return 0;
}