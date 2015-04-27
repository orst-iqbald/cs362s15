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
	initializeGame(2, cards, 10, game);	
	int playerTurn;
	
	game->whoseTurn = 1;
	playerTurn = whoseTurn(game);
	if (playerTurn == 1) {
		printf("Current turn correct\n");
	} 
	else {
		printf("Current turn incorrect\n");
	}

	game->whoseTurn = 0;
	playerTurn = whoseTurn(game);
	if (playerTurn == 1) {
		printf("Current turn correct\n");
	} 
	else {
		printf("Current turn incorrect\n");
	}

	return 0;
}