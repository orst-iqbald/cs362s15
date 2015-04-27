/*
	Testing the Cutpurse Card
	+$2
	Each other player discards a Copper card
	(or reveals a hand with no Copper).
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState *g = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, g);

	printf ("TESTING newCutpurse() card:\n");
    int p, i;
    int copperCount1=0, copperCount2=0;
    int coin1, coin2;
    for(p = 0; p < numPlayer; p++){
        g->whoseTurn = p;
	    g->hand[p][0] = cutpurse;
        g->hand[p][0] = copper;
        
        for(i=0; i< g->handCount[p]; i++)
            if(g->hand[p][i] == copper)
                copperCount1++;
        coin1 = g->coins;
        
        newCutpurse(p, 0, g);
        
        for(i=0; i< g->handCount[p]; i++)
            if(g->hand[p][i] == copper)
                copperCount2++;
        coin2 = g->coins;
        
        if(p&&(copperCount2 != copperCount1+2)){
        	printf("\tFailed - Player %d copper cards did not decrement properly: Expected %d, Returned %d\n", p, copperCount1-1, copperCount2 );
        }
        if(p==0&&(coin2 != coin1+2)){
        	printf("\tFailed - Player %d coins did not increment properly: Expected %d, Returned %d\n", p, coin1+2, coin2);
        }
    }
    printf ("FINISHED newCutpurse() card:\n\n");
	return 0; 
}