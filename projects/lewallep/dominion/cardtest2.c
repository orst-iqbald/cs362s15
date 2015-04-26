#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void adventurerTest(struct gameState *state, int currentPlayer, int z)
{
	int hSize = 100;
	int i = 0;
	int temphand[30];
	int initialHand[100];
	int handCountStart = 0;
	int handCountFinish = 0;
	int treasureStart = 0;
	int treasureFinish = 0;
	int nonTreasure = 0;

	handCountStart = state->handCount[currentPlayer];

	for (i = 0; i < 10; i++)
	{
		if (state->hand[currentPlayer][i] == 4)
		{
			treasureStart++;
		}
		else if (state->hand[currentPlayer][i] == 5)
		{
			treasureStart++;
		}
		else if (state->hand[currentPlayer][i] == 6)
		{
			treasureStart++;
		}
	}
	
	adventurerCard(state, currentPlayer, z, temphand);

	handCountFinish = state->handCount[currentPlayer];

	for (i = 0; i < handCountFinish; i++)
	{
		if (state->hand[currentPlayer][i] == copper)
			treasureFinish++;
		else if (state->hand[currentPlayer][i] == silver)
			treasureFinish++;
		else if (state->hand[currentPlayer][i] == gold)
			treasureFinish++;
	}

	if ((handCountFinish - handCountStart) == 2)
		printf("adventurerCard(): PASSED  Two cards were added.\n");
	else
		printf("adventurerCard(): FAILED  Two cards were not added to the hand\n");

	if ((treasureFinish - treasureStart) == 2)
		printf("adventureCard(): PASSED  Two treausre cards were added.\n");
	else
		printf("adventureCard(): FAILED  Two treasure cards were not added.\n");

	return;
}

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	int players = 2;
	gameStatus = initializeGame(players, k, 12, game);

	adventurerTest(game, 1, 0);
	adventurerTest(game, 0, 0);
	adventurerTest(game, 1, 1);
	adventurerTest(game, 0, 1);


	return 0;
}
