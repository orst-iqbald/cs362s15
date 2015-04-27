#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void tHandCard(int handPos, struct gameState *state, int currentPlayer);

void tHandCard(int handPos, struct gameState *state, int currentPlayer)
{

	state->whoseTurn = currentPlayer;
	state->hand[currentPlayer][handPos] = handPos;

	if (state->hand[currentPlayer][handPos] == handCard(handPos, state))
		printf("handCard(): PASSED\n");
	else
		printf("handCard(): FAILED\n");

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

	tHandCard(0, game, 0);
	tHandCard(9, game, 0);
	tHandCard(0, game, 1);
	tHandCard(9, game, 1);
	tHandCard(5, game, 0);
	tHandCard(5, game, 1);

	free(game);

	return 0;
}