#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void makeTurn(struct gameState *game, int turn);
void testTurn(struct gameState *game, int turn);

void makeTurn(struct gameState *game, int turn)
{
	game->whoseTurn = turn;

	return;
}

void testTurn(struct gameState *game, int turn)
{
	int currentTurn = whoseTurn(game);
	if (currentTurn == turn)
		printf("currentTurn(): PASS when turrentTurn = %d\n", turn);
	else
		printf("currentTurn(): FAIL when currentTurn = %d\n", turn);

	return;
}

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	int players = 3;

	gameStatus = initializeGame(players, k, 10, game);
	
	makeTurn(game, 2);
	testTurn(game, 2);

	makeTurn(game, 1);
	testTurn(game, 1);

	makeTurn(game, 0);
	testTurn(game, 0);

	return 0;
}