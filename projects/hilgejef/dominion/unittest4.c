#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int isHandCard(int handPos, struct gameState *state, int currentPlayer);

int isHandCard(int handPos, struct gameState *state, int currentPlayer)
{
	state->whoseTurn = currentPlayer;
	state->hand[currentPlayer][handPos] = handPos;

	if (state->hand[currentPlayer][handPos] == handCard(handPos, state)) {
		return 1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 10, game);

	if (isHandCard(0, game, 0)) {
		printf("Correct hand card placement\n");
	}
	else {
		printf("Incorrect hand card placement\n");
	}
	if (isHandCard(9, game, 0)) {
		printf("Correct hand card placement\n");
	}
	else {
		printf("Incorrect hand card placement\n");
	}
	if (isHandCard(0, game, 1)) {
		printf("Correct hand card placement\n");
	}
	else {
		printf("Incorrect hand card placement\n");
	}
	if (isHandCard(9, game, 1)) {
		printf("Correct hand card placement\n");
	}
	else {
		printf("Incorrect hand card placement\n");
	}
	if (isHandCard(5, game, 0)) {
		printf("Correct hand card placement\n");
	}
	else {
		printf("Incorrect hand card placement\n");
	}
	if (isHandCard(5, game, 1)) {
		printf("Correct hand card placement\n");
	}
	else {
		printf("Incorrect hand card placement\n");
	}

	free(game);

	return 0;
}