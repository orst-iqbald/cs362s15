/* -----------------------------------------------------------------------
 * Test Gaincard()
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
    int p, r, handCount, supplyPos, toFlag, a, b, c, d;
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

    printf ("TESTING gainCard():\n");
	
supplyPos = 1;

for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (toFlag = 0; toFlag < 3; toFlag++)
            {

                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				
				a = G.deckCount[p];
				b = G.handCount[p];
				c = G.discardCount[p];
				d = G.supplyCount[supplyPos] ;
				
				gainCard(supplyPos, &G, toFlag, p);
			
				
					
				  if (toFlag == 1)
					{
#if (NOISY_TEST == 1)
						printf("Check if the card is added to the deck during player %d's turn\n", p);
#endif	
						assert(G.deckCount[p] == a+1);
#if (NOISY_TEST == 1)
						printf("=====The card has been added\n");
#endif	
					}

				  else if (toFlag == 2)
					{
#if (NOISY_TEST == 1)
						printf("Check if the card is added to the hand during player %d's turn\n", p);
#endif	
						assert(G.handCount[p] == b+1);
#if (NOISY_TEST == 1)
						printf("=====The card has been added\n");
#endif	
					}
				  else
					{
#if (NOISY_TEST == 1)
						printf("Check if the card is added to the discard during player %d's turn\n", p);
#endif	
						assert(G.discardCount[p] == c+1);
#if (NOISY_TEST == 1)
						printf("=====The card has been added\n");
#endif	
					}
					
#if (NOISY_TEST == 1)
						printf("Check if the number in discard pile has been decreased by 1 during player %d's turn\n", p);
#endif	
						assert(G.supplyCount[supplyPos] == d-1);
#if (NOISY_TEST == 1)
						printf("=====The number has been decreased\n");
#endif	
				

#if (NOISY_TEST == 1)
                printf("When supply pile is empty (0) or card is not used in game\n");
#endif				
				G.supplyCount[supplyPos] = 0;

				assert (gainCard(supplyPos, &G, toFlag, p) == -1);
#if (NOISY_TEST == 1)
                printf("Card not gained\n");
#endif	
			
				
				
				
			}
		}
	}			

    printf("All tests passed!\n");

    return 0;
}
