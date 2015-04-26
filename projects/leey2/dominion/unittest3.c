/* -----------------------------------------------------------------------
 * test discardCard()
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
    int p, r, handCount, trashFlag, handPos, a, b;
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

    printf ("TESTING discardCard():\n");
	
for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
			for (trashFlag = 0; trashFlag < 2; trashFlag++){
				handPos = handCount-1;
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
				a = G.playedCardCount;
				b = G.handCount[p];
				discardCard(handPos, p, &G, trashFlag);


#if (NOISY_TEST == 1)
                printf("If card is not trashed, check if it is added to Played pile during player %d's turn\n", p);
#endif				
				if (trashFlag == 0){

						assert(G.playedCardCount == a+1);

#if (NOISY_TEST == 1)
                printf("=====The card is added to Played pile \n");
#endif	
				}
				
#if (NOISY_TEST == 1)
                printf("Check if played card is set to -1 during player %d's turn\n", p);
#endif		
				  assert(G.hand[p][handPos] == -1);
#if (NOISY_TEST == 1)
                printf("=====Played card has been set to -1 during player %d's turn\n", p);
#endif						  
				  
				  if ( handPos == 0 ) 	//last card in hand array is played
					{
#if (NOISY_TEST == 1)
						printf("Check if number of cards in hand is reduced by 1 if last card in hand array is played during player %d's turn\n", p);
#endif							
					  assert(G.handCount[p] == b-1);				  
#if (NOISY_TEST == 1)
						printf("=====The number of cards in hand has been reduced by 1.\n");
#endif		
					}
				  else if ( G.handCount[p] == 1 ) //only one card in hand
					{
#if (NOISY_TEST == 1)
						printf("Check if number of cards in hand is reduced by 1 if there's only one card in hand during player %d's turn\n", p);
#endif	
					  assert(G.handCount[p] == b-1);
#if (NOISY_TEST == 1)
						printf("=====The number of cards in hand has been reduced by 1.\n");
#endif		
					}
				  else 	
					{

#if (NOISY_TEST == 1)
						printf("Check if number of cards in hand is reduced by 1 if there's more than one card in hand during player %d's turn\n", p);
#endif		
					  assert(G.handCount[p] == b-1);
#if (NOISY_TEST == 1)
						printf("=====The number of cards in hand has been reduced by 1.\n");
#endif		
					}

			}	  
				  
		}				
}			

    printf("All tests passed!\n");

    return 0;
}
