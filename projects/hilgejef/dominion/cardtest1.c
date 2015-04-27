#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int playSmithyCard(struct gameState *state, int currentPlayer, int handPos, int hCount)
{
	state->handCount[currentPlayer] = hCount;

	int initialCount = state->handCount[currentPlayer];

	playSmithy(state, currentPlayer, handPos);

	int finalCount = state->handCount[currentPlayer];

	return finalCount - initialCount;
}

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 10, game);

	if (playSmithyCard(game, 1, 2, 0) == 2) {
		printf("Correct number of cards added by Smithy\n");
	}
	else {
		printf("Incorrect number of cards added by Smithy\n");
	}

	if (playSmithyCard(game, 1, 2, 1) == 2) {
		printf("Correct number of cards added by Smithy\n");
	}
	else {
		printf("Incorrect number of cards added by Smithy\n");
	}

	if (playSmithyCard(game, 1, 2, 2) == 2) {
		printf("Correct number of cards added by Smithy\n");
	}
	else {
		printf("Incorrect number of cards added by Smithy\n");
	}

	if (playSmithyCard(game, 1, 2, 3) == 2) {
		printf("Correct number of cards added by Smithy\n");
	}
	else {
		printf("Incorrect number of cards added by Smithy\n");
	}

	return 0;
}