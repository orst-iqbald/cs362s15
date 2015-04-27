/*
    Testing the Smithy Card
    +3 Cards.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState *g = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, g);
    
    printf ("TESTING newSmithy() card:\n");
    int p;
    for(p = 0; p < numPlayer; p++){
        g->whoseTurn = p;
        g->hand[p][0] = smithy;
        
        int cards = g->handCount[p];
        newSmithy(p, 0, g);
        if(g->handCount[p] != (cards+2)){
            printf("\tFailed - Player %d number of cards in hand incorrect. Expected = %d, Returned = %d\n", p, cards+2,g->handCount[p]);
        }
    }
    printf ("FINISHED newSmithy() card:\n\n");
  return 0;
}