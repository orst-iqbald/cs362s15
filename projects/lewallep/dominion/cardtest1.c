#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void tSmithyCard(struct gameState *state, int currentPlayer, int handPos, int hCount);

void tSmithyCard(struct gameState *state, int currentPlayer, int handPos, int hCount)
{
	state->handCount[currentPlayer] = hCount;

	int initialCount = state->handCount[currentPlayer];
	int finalCount = 0;

	smithyCard(state, currentPlayer, handPos);

	finalCount = state->handCount[currentPlayer];

	if (finalCount - initialCount == 2)
		printf("smithyCard(): PASSED  Initial handCount: %d  Final handCount: %d\n", initialCount, finalCount);
	else
		printf("smithyCard(): FAILED  Initial handCount: %d  Final handCount: %d\n", initialCount, finalCount);

	return;
}

int main(int argc, char **argv)
{

	struct gameState *game = newGame();
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	int players = 2;

	gameStatus = initializeGame(players, k, 10, game);

	tSmithyCard(game, 1, 2, 1);
	tSmithyCard(game, 1, 2, 0);
	tSmithyCard(game, 1, 2, 5);
	tSmithyCard(game, 1, 2, 10);

	return 0;
}