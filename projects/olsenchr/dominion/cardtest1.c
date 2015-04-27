/************************
 * Card Test for Smithy
 ***********************/

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
	int k[10] = {adventurer, smithy, great_hall, council_room, feast, gardens, mine, remodel, village, baron};

	printf("Testing Smithy...\n");

	r = initializeGame(2, k, 1000, &G); 
	//Make sure Smithy gets removed from hand
	G.handCount[1] = 5;
	p = playSmithy(&G, 1, 1);
	//Make sure hand increases to proper size
	assert (G.handCount[1] == 7);
	printf("Passed test 1\n");
		
	//Test when player has no actions
	G.numActions = 0;
	p = playSmithy(&G, 1, 1);
	printf("Bug\n");

	return 0;
}
