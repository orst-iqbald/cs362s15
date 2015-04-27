/*
    Testing the Adventurer Card
    Reveal cards from your deck until you reveal 2 Treasure cards.
    Put those Treasure cards in your hand and discard the other revealed cards.
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

	printf ("TESTING newAdventurer() card:\n");
    int p;
    for(p = 0; p < numPlayer; p++){
        g->whoseTurn = p;
        int cards1 = 0;
        int cards2 = 0;
        g->hand[p][0] = adventurer;
        int i;
      	for(i=0; i< g->handCount[p]; i++){
            int card = g->hand[p][i];
            if(card == copper || card == silver || card == gold){
                cards1++;
            }
        }
        newAdventurer(p, g);
        for(i=0; i< g->handCount[p]; i++){
            int card = g->hand[p][i];
            if(card == copper || card == silver || card == gold){
                cards2++;
            }
        }
        if(cards1 != cards2){
            printf("\tFailed - Player %d number of treasure cards incorrect. Expected = %d, Returned = %d\n", p, cards1+2, cards2);
        }
    }
    printf ("FINISHED newAdventurer() card:\n\n");
	return 0; 
}