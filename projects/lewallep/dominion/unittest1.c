#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void fillHand(struct gameState *gameOne, int player, int cardChoice, int handSize);
void testHand(struct gameState *gameOne, int handCount, int bonus);

void fillHand(struct gameState *gameOne, int player, int cardChoice, int handSize)
{
	int i = 0; 
	gameOne->handCount[player] = handSize;

	for(i = 0; i < gameOne->handCount[player]; i++)
	{
		gameOne->hand[player][i] = cardChoice;
	}

	return;
}

void testHand(struct gameState *gameOne, int handCount, int bonus) 
{
	if (gameOne->coins == (handCount * 1) + bonus)
		printf("updateCoins(): PASS with handCount: %d, cardChoice: COPPER, bonus: %d\n", handCount, bonus);
	else if (gameOne->coins == (handCount * 2) + bonus)
		printf("updateCoins(): PASS with handCount: %d, cardChoice: SILVER, bonus: %d\n", handCount, bonus);
	else if (gameOne->coins == (handCount * 3) + bonus)
		printf("updateCoins(): PASS with handCount: %d, cardChoice: GOLD, bonus: %d\n", handCount, bonus);
	else
		printf("updateCoins(): FAIL\n");

	return;
}

int main(int argc, char **argv)
{
	int eValueUpdateCoins;
	int gameStatus;
 	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
        sea_hag, tribute, smithy};
	struct gameState *gameOne = newGame();
	int player = 0;
	int handCount = 20;
	int bonus = 100;
	int numPlayers = 2;

	gameStatus = initializeGame(numPlayers, k, 6, gameOne);

	//Set all of the coins to copper
	fillHand(gameOne, player, copper, handCount);
	eValueUpdateCoins = updateCoins(player, gameOne, bonus);
	testHand(gameOne, handCount, bonus);

	fillHand(gameOne, player, silver, handCount);
	eValueUpdateCoins = updateCoins(player, gameOne, bonus);
	testHand(gameOne, handCount, bonus);

	fillHand(gameOne, player, gold, handCount);
	eValueUpdateCoins = updateCoins(player, gameOne, bonus);
	testHand(gameOne, handCount, bonus);

	handCount = 2;

	fillHand(gameOne, player, copper, handCount);
	eValueUpdateCoins = updateCoins(player, gameOne, bonus);
	testHand(gameOne, handCount, bonus);

	fillHand(gameOne, player, silver, handCount);
	eValueUpdateCoins = updateCoins(player, gameOne, bonus);
	testHand(gameOne, handCount, bonus);

	fillHand(gameOne, player, gold, handCount);
	eValueUpdateCoins = updateCoins(player, gameOne, bonus);
	testHand(gameOne, handCount, bonus);


	free(gameOne);

	return 0;
}