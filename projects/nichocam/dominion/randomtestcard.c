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
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int i, j, k, count, test;
	int allcards[27] = { curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };
	initializeGame(3, cards, 55555, test1);     //My favorite number is 5 so the seed is 5 5's
	test1->hand[0][0] = smithy;             //ensure adventurer is in the hand


	srand(time(NULL));


	printf("Start of Smithy random test\n"); //Opening message

	for (test = 0; test < 1000000; test++){
		//build random hand
		for (count = 1; count < 4; count++){
			test1->hand[0][count] = allcards[rand() % 10];
		}
		int handsize = test1->handCount[0];
		memcpy(test2, test1, sizeof(struct gameState)); // to compare it to

		i = rand();
		j = rand();
		k = rand();

		playCard(0, i, j, k, test1);

		if (memcmp(test1, test2, sizeof(struct gameState)) == 0){
			printf("Failed to get new cards i= %d j= %d k= %d. Hand is:  ", i, j, k);
			for (count = 0; count < test1->handCount[0]; count++)
				printf(test1->hand[0][count]);
			printf("\n");
		}

		if (test1->hand[0][0] == smithy && handsize == test1->handCount[0]){
			printf("Failed to discard Smithy i= %d j= %d k= %d. Hand is:  ", i, j, k);
			for (count = 0; count < test1->handCount[0]; count++)
				printf(test1->hand[0][count]);
			printf("\n");
		}


		if (test % 10000 == 0)
			printf("%d tests completed\n", test);
		memcpy(test1, test2, sizeof(struct gameState));
	}
	return 0;
}
