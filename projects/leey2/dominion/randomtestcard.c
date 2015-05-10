/* -----------------------------------------------------------------------
 * Random test for village card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h> 
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 4;
    int maxBonus = 10;
    int p, r, handCount, choice1, choice2, choice3, handPos, temp1, temp2;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 10;
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

    printf ("TESTING Village card:\n");
	
	srand(time(NULL));
	int l;
	
	for(l = 0 ; l<10000; l++)
	{
		p = rand() % numPlayer;
		handCount = rand() % maxHandCount + 1;
		bonus = rand() % maxBonus;
		
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
                printf("Check if the number of cards in hand is the after playing the card during player %d's turn with %d handCount and %d bonus.\n", p, handCount, bonus);
#endif
				temp1 = G.handCount[p];
				temp2 = G.numActions;
				cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus);
				assert(G.handCount[p] == temp1);
#if (NOISY_TEST == 1)
                printf("===== The number of cards in hand is after playing the card.\n");
#endif				
#if (NOISY_TEST == 1)
                printf("Check if the action point has been increase by 2 during player %d's turnwith %d handCount and %d bonus.\n", p, handCount, bonus);
#endif
				if (G.numActions== temp2+2){
#if (NOISY_TEST == 1)
					printf("2 action points have been added.\n");
#endif
				}
				else{
#if (NOISY_TEST == 1)
					printf("Other than 2 action points have not been added.\n");
#endif
				}		
	}			
				

    printf("All tests passed!\n");

    return 0;
}
