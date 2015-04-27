#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int handCountAdventurer(struct gameState *state, int currentPlayer, int z)
{
	int initialCount = state->handCount[currentPlayer];
	int tempHand[30];
	
	playAdventurer(state, currentPlayer, z, tempHand);

	int finalCount = state->handCount[currentPlayer];

	return finalCount - initialCount;
}

int treasureCountAdventurer(struct gameState *state, int currentPlayer, int z)
{
	int i = 0;
	int tempHand[30];
	int initialTreasureCount = 0;
	int finalTreasureCount = 0;

	int initialHandCount = state->handCount[currentPlayer];

	for (i = 0; i < 10; i++)
	{
		if (state->hand[currentPlayer][i] == 4)
		{
			initialTreasureCount++;
		}
		else if (state->hand[currentPlayer][i] == 5)
		{
			initialTreasureCount++;
		}
		else if (state->hand[currentPlayer][i] == 6)
		{
			initialTreasureCount++;
		}
	}
	
	playAdventurer(state, currentPlayer, z, tempHand);

	int handCountFinish = state->handCount[currentPlayer];

	for (i = 0; i < handCountFinish; i++)
	{
		if (state->hand[currentPlayer][i] == copper)
			finalTreasureCount++;
		else if (state->hand[currentPlayer][i] == silver)
			finalTreasureCount++;
		else if (state->hand[currentPlayer][i] == gold)
			finalTreasureCount++;
	}

	return finalTreasureCount - initialTreasureCount;
}


int main(int argc, char **argv)
{
	struct gameState *game = newGame();
 	int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	initializeGame(2, cards, 12, game);

	if (handCountAdventurer(game, 1, 0) == 2) {
		printf("Correct number of cards added by Adventurer");
	}
	else {
		printf("Incorrect number of cards added by Adventurer");	
	}

	if (handCountAdventurer(game, 0, 0) == 2) {
		printf("Correct number of cards added by Adventurer");
	}
	else {
		printf("Incorrect number of cards added by Adventurer");	
	}

	if (handCountAdventurer(game, 1, 1) == 2) {
		printf("Correct number of cards added by Adventurer");
	}
	else {
		printf("Incorrect number of cards added by Adventurer");	
	}

	if (handCountAdventurer(game, 1, 1) == 2) {
		printf("Correct number of cards added by Adventurer");
	}
	else {
		printf("Incorrect number of cards added by Adventurer");	
	}


	if (treasureCountAdventurer(game, 1, 0) == 2) {
		printf("Correct number of treasures added by Adventurer");
	}
	else {
		printf("Incorrect number of treasures added by Adventurer");
	}

	if (treasureCountAdventurer(game, 0, 0) == 2) {
		printf("Correct number of treasures added by Adventurer");
	}
	else {
		printf("Incorrect number of treasures added by Adventurer");
	}

	if (treasureCountAdventurer(game, 1, 1) == 2) {
		printf("Correct number of treasures added by Adventurer");
	}
	else {
		printf("Incorrect number of treasures added by Adventurer");
	}

	if (treasureCountAdventurer(game, 0, 1) == 2) {
		printf("Correct number of treasures added by Adventurer");
	}
	else {
		printf("Incorrect number of treasures added by Adventurer");
	}


	return 0;
}