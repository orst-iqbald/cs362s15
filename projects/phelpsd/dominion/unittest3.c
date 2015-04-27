/* -----------------------------------------------------------------------
 * Test for initializeGame() function in dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 4;
    int p, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));

    printf ("TESTING initializeGame():\n");
    //for loop to test number of players from 0-5 to test cases outside the valid range
    for (p = 0; p <= numPlayer + 1; p++) {  
#if (NOISY_TEST == 1)
        printf("Test initializing a game with %d players.\n", p);
#endif        
        r = initializeGame(p, k, seed, G); //initialize a new game            
#if (NOISY_TEST == 1)
        if (r == -1) {
            printf("Number of players is outside valid range: Tested value %d\n", p);
        }
        else {
            printf("Number of players = %d, expected = %d\n", G->numPlayers, p);
            //curse card initialization tests
            //2p games
            if (G->numPlayers == 2) {
                printf("Curse supply count for %d player game: Actual = %d, Expected = %d\n", 
                G->numPlayers, G->supplyCount[curse], 10);
            }
            //3p games
            if (G->numPlayers == 3) {
                printf("Curse supply count for %d player game: Actual = %d, Expected = %d\n", 
                G->numPlayers, G->supplyCount[curse], 20);
            }
            //4p games
            if (G->numPlayers == 4) {
                printf("Curse supply count for %d player game: Actual = %d, Expected = %d\n", 
                G->numPlayers, G->supplyCount[curse], 30);
            }
            //treasure card initialization tests
            printf("Copper count for %d player game: Actual = %d, Expected = %d\n", 
            G->numPlayers, G->supplyCount[copper], 60 - (7 * p));
            printf("Silver count for %d player game: Actual = %d, Expected = %d\n", 
            G->numPlayers, G->supplyCount[silver], 40);
            printf("Gold count for %d player game: Actual = %d, Expected = %d\n", 
            G->numPlayers, G->supplyCount[gold], 30);
            //victory card initialization tests
            printf("Testing victory card amounts... ");
            if(G->numPlayers == 2 && G->supplyCount[province] == 8) {
                printf("Test Passed for %d player game! Actual = %d, expected = %d\n", p, G->supplyCount[province], 8);
            }
            if((G->numPlayers == 3 || G->numPlayers == 4) && G->supplyCount[province] == 12) {
                printf("Test Passed for %d player game! Actual = %d, expected = %d\n", p, G->supplyCount[province], 12);
            }
        }
        
#endif
    }

    printf("Testing Complete!\n");

    return 0;
}