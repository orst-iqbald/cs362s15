#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void tSupplyCount(struct gameState *game);

void tSupplyCount(struct gameState *game)
{
	int i = 0;
	int setValue = 50;
	int value = 0;

	//Set a unique number of cards for each type of card.
	for (i = 0; i <= treasure_map  + setValue; i++)
	{
		game->supplyCount[i] = setValue + i;
	}

	//Read all of the set values for the number of cards.
	for (i = 0; i <= treasure_map; i++)
	{
		value = supplyCount(i, game); 
		if (value == game->supplyCount[i])
			printf("supplyCount: PASSED.  Input Value = %d, supplyCount() value = %d\n", game->supplyCount[i], value);
		else
			printf("supplyCount: FAILED\n");
	}

	return;
}

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	int players = 2;

	gameStatus = initializeGame(players, k, 15, game);

	tSupplyCount(game);

	free(game);

	return 0;
}