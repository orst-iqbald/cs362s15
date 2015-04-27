/* -----------------------------------------------------------------------
 * Test isGameOver()
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 3;
    int p, r;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    // arrays of all coppers, silvers, and golds
    /*for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }*/

	
	printf ("TESTING isGameOver():\n");
			
for (p = 0; p < numPlayer; p++)
    {	
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
		for (i = 0; i < 25; i++)
		{
		  G.supplyCount[i] = 1;
		}		
		
#if (NOISY_TEST == 1)
        printf("Checks the number of provinces or if three supply piles are empty to determine if the game is over with Player %d's turn\n", p);
#endif		
		for (i = 5; i >= 0; i--)
		{
			G.supplyCount[province] = i;
			isGameOver(&G);
			if (i == 0){
#if (NOISY_TEST == 1)
                printf("When the number of province card left is %d\n", i);
#endif
				assert(isGameOver(&G) == 1);
#if (NOISY_TEST == 1)
                printf("Game ends\n");
#endif
			}	
			else if (i != 0){
#if (NOISY_TEST == 1)
                printf("When the number of province card left is %d\n", i);
#endif
				assert(isGameOver(&G) != 1);
#if (NOISY_TEST == 1)
                printf("Game does not end\n");
#endif
			}
		}	

		for (i= 0; i < 25; i++)
		{
		  G.supplyCount[i] = 1;
		}		

		for (i= 0; i < 3; i++)
		{
			G.supplyCount[i] = 0;
			isGameOver(&G);
		if (i > 1){
#if (NOISY_TEST == 1)
                printf("When the number of empty supply piles is %d\n", i+1);
#endif
				assert(isGameOver(&G) == 1);
#if (NOISY_TEST == 1)
                printf("Game ends\n");
#endif
			}	
			else {
#if (NOISY_TEST == 1)
                printf("When the number of empty supply piles is %d\n", i+1);
#endif
				assert(isGameOver(&G) == 0);
#if (NOISY_TEST == 1)
                printf("Game does not end\n");
#endif
			}

		}
}	

	
    printf("All tests passed!\n");

    return 0;
}