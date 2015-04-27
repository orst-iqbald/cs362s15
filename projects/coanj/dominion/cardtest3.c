/*
	Testing the Baron Card
	+1 Buy
	You may discard an Estate card. 
	If you do, +$4. Otherwise, gain an Estate card.
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
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState *g = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, g);

	printf ("TESTING newBaron() card:\n");
	int estateCount1 = 0, estateCount2 = 0;
	int coin1 = 0, coin2 = 0;
    int p, i;
    for(p = 0; p < numPlayer; p++){
        g->whoseTurn = p;
        g->hand[p][0] = baron;
        g->hand[p][1] = estate;
        
        int buy1 = g->numBuys;
        coin1 = g->coins;
        
        for(i=0; i < g->handCount[p]; i++)
            if(g->hand[p][i] == estate)
                estateCount1++;
            
        newBaron(p, p, g);
        
        for(i=0; i < g->handCount[p]; i++)
            if(g->hand[p][i] == estate)
                estateCount2++;
            
        int buy2 = g->numBuys;
        coin2 = g->coins;
        
        
        if(buy1 == buy2){
        	printf("\tFailed - Player %d buy not incremented properly: Expected %d, Returned %d\n", p, buy1+1, buy2 );
        }
        if(p && (estateCount1==estateCount2)){
        	printf("\tFailed - Player %d estate count not decremented after choosing to discard. Expected = %d, Returned = %d\n",p,estateCount1-1,estateCount2);
        }
        if(p==1 && (coin1==coin2)){
        	printf("\tFailed - Player %d coin count not increase after choosing to discard estate. Expected = %d, Returned = %d\n",p,coin1+4,coin2);
        }
        g->whoseTurn++;
    }
    printf ("FINISHED newBaron() card:\n\n");
	return 0; 
}