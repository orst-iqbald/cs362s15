#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void tVillage(int currentPlayer, struct gameState *state, int handPos)
{
	int cardsStart = 0;
	int cardsFinish = 0;
	int actionsStart = 0;
	int actionsFinish = 0;
	//Test the increase in the number of actions.
	actionsStart = state->numActions;
	cardsStart = state->handCount[currentPlayer];
	//Test for a card to be drawn

	villageCard(currentPlayer, state, handPos);

	actionsFinish = state->numActions;
	cardsFinish = state->handCount[currentPlayer];
	//Test that the village card is discarded.

	/*
	printf("actionsStart %d\n", actionsStart);
	printf("actionsFinish %d\n", actionsFinish);
	printf("cardsStart %d\n", cardsStart);
	printf("cardsFinish %d\n", cardsFinish);
	*/

	if (actionsFinish - actionsStart == 2)
		printf("villageCard() ACTIONS: PASSED\n");
	else
		printf("villageCard() ACTIONS: FAILED\n");

	if (cardsFinish == cardsStart)
		printf("villageCard() Card Count: PASSED\n");
	else
		printf("villageCard() Card Count: FAILED\n");

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

	tVillage(1, game, 0);
	tVillage(0, game, 0);
	tVillage(1, game, 1);
	tVillage(1, game, 1);

	return 0;
}