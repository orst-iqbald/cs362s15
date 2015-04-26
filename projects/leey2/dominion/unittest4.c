/* -----------------------------------------------------------------------
 * fullDeckCount()
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
    int p, r, handCount, z, u;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING fullDeckCount():\n");
	
	int card = 100;
	
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (z = 1; z <= maxHandCount; z++)
            {
				
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = 5;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				G.discardCount [p] = 5 ; 
				G.deckCount[p] = 5; 
				
				if (handCount == 1){
#if (NOISY_TEST == 1)
					printf("There are %d number of matching cards in deck.\n", z);
#endif
					for (u=0; u < z; u++){
						G.deck[p][u]= 100;
					}
					assert (fullDeckCount(p, card, &G) == z);
#if (NOISY_TEST == 1)
					printf("=====Test passed.\n");
#endif
				}
				else if (handCount == 2){
#if (NOISY_TEST == 1)
					printf("There are %d number of matching cards in deck.\n", z*2);
#endif
					for (u=0; u < z; u++){
						G.deck[p][u]= 100;
						G.hand[p][u] = 100;
					}	
					assert (fullDeckCount(p, card, &G) == z*2);

#if (NOISY_TEST == 1)
					printf("=====Test passed.\n");
#endif
				}
				else if (handCount == 3){
#if (NOISY_TEST == 1)
					printf("There are %d number of matching cards in deck.\n", z*2);
#endif
					for (u=0; u < z; u++){
						G.deck[p][u]= 100;
						G.discard[p][u] = 100;
					}	
					assert (fullDeckCount(p, card, &G) == z*2);

#if (NOISY_TEST == 1)
					printf("=====Test passed.\n");
#endif
				}
				else if (handCount == 4){
#if (NOISY_TEST == 1)
					printf("There are %d number of matching cards in deck.\n", z*2);
#endif
					for (u=0; u < z; u++){
						G.hand[p][u]= 100;
						G.discard[p][u] = 100;
					}	
					assert (fullDeckCount(p, card, &G) == z*2);

#if (NOISY_TEST == 1)
					printf("=====Test passed.\n");
#endif
				}
				else{
#if (NOISY_TEST == 1)
					printf("There are %d number of matching cards in deck.\n", z*3);
#endif
					for (u=0; u < z; u++){
						G.deck[p][u]= 100;
						G.hand[p][u] = 100;
						G.discard[p][u] = 100;
					}	
					assert (fullDeckCount(p, card, &G) == z*3);

#if (NOISY_TEST == 1)
					printf("=====Test passed.\n");
#endif
				}



			}
		}
	}
	

    printf("All tests passed!\n");

    return 0;
}
