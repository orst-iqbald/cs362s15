#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, great_hall, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 12, game);	

	int initialHandCount = game->handCount[0];
	int initialNumActions = game->numActions;

	playGreatHall(0, game, 0);

	int finalHandCount = game->handCount[0];
	int finalNumActions = game->numActions;

	if (finalNumActions - initialNumActions == 0) {
		printf("Correct great hall number of actions\n");
	}
	else {
		printf("Incorrect great hall number of actions\n");
	}

	if (finalHandCount - initialHandCount == 4) {
		printf("Correct great hall number of cards\n");
	}
	else {
		printf("Incorrect great hall number of cards\n");
	}

	return 0;
}