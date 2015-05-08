#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

int main() {

	//Initializing game state
	struct gameState *test1 = malloc(sizeof(struct gameState));
	struct gameState *test2 = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall }, i, j, k;
	initializeGame(3, cards, 55555, test1);     //My favorite number is 5 so the seed is 5 5's
	test1->hand[0][0] = smithy;             //ensure smithy is in the hand
	test1->hand[0][1] = mine;             //ensure adventurer is not second
	memcpy(test2, test1, sizeof(struct gameState));

	srand(time(NULL));


	printf("Start of Smithy random test\n"); //Opening message
	for (;;){
		i = rand();
		j = rand();
		k = rand();

		playCard(0, i, j, k, test1);

		if (memcmp(test1, test2, sizeof(struct gameState)) == 0)
			printf("\n!!!!!\nFailed to get new cards i= %d j= %d k= %d.\n!!!!!\n\n", i, j, k);

		if (test1->hand[0][0] == adventurer)
			printf("\n!!!!!\nFailed to discard adventurer i= %d j= %d k= %d.\n!!!!!\n\n", i, j, k);

		memcpy(test1, test2, sizeof(struct gameState));
	}
	return 0;
}
