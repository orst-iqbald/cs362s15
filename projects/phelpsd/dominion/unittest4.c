/* -----------------------------------------------------------------------
 * Test for handCard() function in dominion.c
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
    int numPlayer = 2;
    int i, p, r;
    int handCount = 5;
    const char *cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
    "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
    "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G); //initialize a new game
    
    printf ("TESTING handCard():\n");
    for (p = 0; p < numPlayer; p++) {  
#if (NOISY_TEST == 1)
        printf("Testing cards in player %d's hand.\n", p);
#endif
        G->whoseTurn = p;
        //sets up first players hand
        if (p == 0) {
            G->hand[p][0] = village; //sets the first card in the players hand
            G->hand[p][1] = copper; //sets the second card in the players hand
            G->hand[p][2] = smithy; //sets the third card in the players hand
            G->hand[p][3] = feast; //sets the fourth card in the players hand
            G->hand[p][4] = gardens; //sets the fifth card in the players hand
        }
        //sets up second players hand
        if (p == 1) {
            G->hand[p][0] = gold; //sets the first card in the players hand
            G->hand[p][1] = adventurer; //sets the second card in the players hand
            G->hand[p][2] = council_room; //sets the third card in the players hand
            G->hand[p][3] = remodel; //sets the fourth card in the players hand
            G->hand[p][4] = mine; //sets the fifth card in the players hand
        }
        for (i = 0; i < handCount; ++i) {
            r = handCard(i, G);
#if (NOISY_TEST == 1)
            if (G->hand[p][i] == r) {
                printf("Test Passed! Card %d in player %d's hand is %s\n", i, p, cardNames[r]);
            }
            else {
                printf("Test Failed.\n"); 
            }
        }
        
#endif

    }

    printf("Testing Complete!\n");

    return 0;
}