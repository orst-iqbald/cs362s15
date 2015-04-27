/* -----------------------------------------------------------------------
 * test Adventure card
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
    int maxBonus = 5;
    int p, r, handCount, choice1, choice2, choice3, handPos, cardDrawn, temp ;
    int bonus;
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

    printf ("TESTING Adventurer card:\n");
	
   for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
				handPos = handCount;
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				choice1 = p;
				choice2 = p;
				choice3 = p;
				G.whoseTurn = p;
#if (NOISY_TEST == 1)
                printf("Check if the number of cards in hand has been increased by 2 during player %d's turn.\n", p);
#endif
				temp = G.handCount[p];
				cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
				assert(G.handCount[p] == temp+2);
#if (NOISY_TEST == 1)
                printf("===== The number of cards in hand has been increased by 2 during player %d's turn.\n", p);
#endif				
#if (NOISY_TEST == 1)
                printf("Check if 2 drawn cards are treasure cards during player %d's turn.\n", p);
#endif
				cardDrawn = G.hand[p][G.handCount[p]-1];
				assert(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold);
				cardDrawn = G.hand[p][G.handCount[p]-2];
				assert(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold);
#if (NOISY_TEST == 1)
                printf("=====2 drawn cards are treasure cards.\n");
#endif
			}	
		}		
	}			
				

    printf("All tests passed!\n");

    return 0;
}
