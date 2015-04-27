#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(int argc, char **argv)
{
	struct gameState *game = newGame();
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	int players = 2;
	gameStatus = initializeGame(players, k, 12, game);

	int testValue = 100;

	testValue = gardensCard();

	if (testValue == -1)
		printf("gardensCard(): PASSED\n");
	else
		printf("gardensCard(): FAILED\n");

	return 0;
}
