#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 15, game);	
	int i;
	int currentSupply;

	for (i = 0; i <= treasure_map + 50; i++)
	{
		game->supplyCount[i] = 50 + i;
	}

	for (i = 0; i <= treasure_map; i++)
	{
		currentSupply = supplyCount(i, game); 
		if (currentSupply == game->supplyCount[i]) {
			printf("Supply count correct\n");
		}
		else {
			printf("Supply count incorrect\n");
		}
	}	

	free(game);

	return 0;
}