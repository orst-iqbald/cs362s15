/*
 *             Author: Michael Marven
 *       Date Created: 04/26/15
 * Last Date Modified: 04/26/15
 *          File Name: unittest1.c
 *           Overview: Program to test shuffle() in dominion.c; Tests that the
 *                     shuffled decks are different from the original and that
 *                     they have the same number of cards in the deck as before
 *                     the shuffle
 *
 *                     Add the following lines to the makefile:
 *                     unittest1: unittest1.c dominion.o rngs.o
 *                         gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int e, i, p, r, t;
    int player;
    int card;
    int deckCount;
    int randDeckOrig[MAX_DECK];
    int numPlayers = 2;
    int seed       = 1000;
    int k[10]      = {adventurer, council_room, feast, gardens, mine, remodel, 
                      smithy, village, baron, great_hall};
    
    struct gameState G;
    
    // Clear the game state
    memset(&G, 0, sizeof(struct gameState));
    
    // Initialize game state
    r = initializeGame(numPlayers, k, seed, &G);
    
    
    printf("TESTING shuffle():\n");
    for (t = 0; t < NUM_OF_TESTS; t++)
    {
        printf("Test cycle %d, %d players\n", t, numPlayers);
        for (p = 0; p < numPlayers; p++)
        {
            player = p;
            
            // Generate a random deck count and deck
            deckCount = rand_range(1, MAX_DECK);
            for (i = 0; i < deckCount; i++)
            {
                card = rand_range(curse, treasure_map);
                randDeckOrig[i] = card;
            }
            
            // Copy random deck and deckCount to game state for player
            memcpy(G.deck[player], randDeckOrig, sizeof(int) * deckCount);
            G.deckCount[player] = deckCount;
            
#if (NOISY_TEST == 1)
            printf("Test player %d's deck is shuffled.\n", player);
#endif
            shuffle(player, &G);
            
            /*
             * Two tests are performed to check that the shuffled deck is
             * different from the original, and has the same amount of cards as
             * the initial deck
             */
            assert(memcmp(G.deck[player], randDeckOrig, 
                   sizeof(int) * deckCount) != 0);
            assert(G.deckCount[player] == deckCount);
            
#if (NOISY_TEST == 1)
            printf("Test for correct action if deck has 0 cards.\n");
#endif
            // Set deckCount to 0
            G.deckCount[player] = 0;
            
            e = shuffle(player, &G);
            assert(e == -1);

        }
    }
    
    printf("All tests passed!\n");

    return 0;
}