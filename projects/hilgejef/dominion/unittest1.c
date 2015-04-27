#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void handFill(struct gameState *gameOne, int player, int card, int handSize);

void handFill (struct gameState *game, int player, int card, int handSize)
{
	int i;

	game->handCount[player] = handSize;

	for(i = 0; i < game->handCount[player]; i++)
	{
		game->hand[player][i] = card;
	}

	return;
}

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 6, game);	

	handFill(game, 0, copper, 20);
	updateCoins(0, game, 10);
	if (game->coins == 20 + 10) {
		printf("All copper hand passed\n");
	}
	else {
		printf("All copper hand failed\n");
	}

	handFill(game, 0, silver, 20);
	updateCoins(0, game, 10);
	if (game->coins == (20 * 2) + 10) {
		printf("All silver hand passed\n");
	}
	else {
		printf("All silver hand failed\n");
	}

	handFill(game, 0, gold, 20);
	updateCoins(0, game, 10);
	if (game->coins == (20 * 3) + 10) {
		printf("All gold hand passed\n");
	}
	else {
		printf("All gold hand failed\n");
	}

	free(game);

	return 0;
}