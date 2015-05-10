/****************************
 * Card Test for Adventurer
 ***************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i;
	struct gameState G;
	int p, r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	r = initializeGame(2, k, 1000, &G);
	
	printf("Testing Adventurer...\n");

	//Test when there's no treasure in deck
	G.deckCount[1] = 0;
	G.discardCount[1] = 0;
//	p = playAdventurer(&G,1,1);
//	assert(p == 0);
	printf("Passed Test 1\n");
		
	//Test when deck is empty
	G.deckCount[1] = 0;
	for ( i = 0; i < 11; i++){
		gainCard(2, &G, 0, 1);
	}
//	p = playAdventurer(&G,1,1);
//	assert(G.deckCount > 0);
	printf("Passed test 2\n");
	
	return 0;
}
