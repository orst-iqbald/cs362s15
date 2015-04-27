#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 12, game);	


	int initialHandCount = game->handCount[0];
	int initialNumBuys = game->numBuys;

	playCouncilRoom(0, game, 0);

	int finalHandCount = game->handCount[0];
	int finalNumBuys = game->numBuys;

	if (finalNumBuys - initialNumBuys == 1) {
		printf("Correct council room number of buys\n");
	}
	else {
		printf("Incorrect council room number of buys\n");
	}

	if (finalHandCount - initialHandCount == 4) {
		printf("Correct council room number of cards\n");
	}
	else {
		printf("Incorrect council room number of cards\n");
	}

	return 0;
}
