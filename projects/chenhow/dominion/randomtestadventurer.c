//Author:                 Howard Chen
//Class/Assignment:       CS362/Assignment 4
//Term:                   Spring 2015
//File Name:              randomtestadventurer.c

/*Description: This is a card test to test the cardAdventurer() in dominion.c.
The test needs to determine whether the cardAdventurer() places the correct
number of treasure cards and then discards.*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testCardAdventurer(int currentPlayer, struct gameState *after)
{
	int discard = 1;
	int failTests = 0;
	int temphand[MAX_HAND];
	int drawnTreasure = 0;
	int cardDrawn = 0;
	int z = 0;
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	while (drawnTreasure < 2)
	{
		if (before.deckCount[currentPlayer] < 1)
		{
			//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &before);
		}

		drawCard(currentPlayer, &before);
		//top card of hand is most recently drawn card.
		cardDrawn = before.hand[currentPlayer][before.handCount[currentPlayer] - 1];

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		{
			drawnTreasure++;
		}
		else
		{
			temphand[z] = cardDrawn;
			//this should just remove the top card (the most recently drawn one).
			before.handCount[currentPlayer]--;
			z++;
		}
	}

	while (z > 0)
	{
		//discard all cards in play that have been drawn
		before.discard[currentPlayer][before.discardCount[currentPlayer]++] = temphand[z - 1];
		z--;
	}

	discardCard((before.handCount[currentPlayer] - 3), currentPlayer, &before, 0);

	cardAdventurer(currentPlayer, after);

	//check to see if top discard pile is not the same
	if (after->playedCards[after->playedCardCount - 1] != before.playedCards[before.playedCardCount - 1])
	{
		//FAILED: discard card
		printf("cardAdventurer() FAIL: DISCARD\n");
		printf("cardAdventurer() INFO: Does NOT DISCARD Card\n");
		discard = 0;
		failTests = 1;
	}
	else
	{
		discard = 1;
	}

	if (drawnTreasure != 2)
	{
		printf("cardAdventurer() FAIL: +2 DRAW TREASURE\n");
		printf("cardAdventurer() INFO: ERROR in drawntreasure VAR\n");
		failTests += 1;
	}

	if (after->hand[currentPlayer][after->handCount[currentPlayer] - 1] != copper ||
		after->hand[currentPlayer][after->handCount[currentPlayer] - 1] != silver || 
		after->hand[currentPlayer][after->handCount[currentPlayer] - 1] != gold)
	{
		printf("cardAdventurer() FAIL: DRAW TREASURE CARD\n");
		printf("cardAdventurer() INFO: ERROR not TREASURE DRAWN\n");
		failTests += 1;
	}

	//if Adventurer card was properly discarded,
	if (discard == 1)
	{
		//then check to see if hand counts don't match
		if (before.handCount[currentPlayer] != after->handCount[currentPlayer])
		{
			//FAILED: +2 draw
			printf("cardAdventurer() FAIL: +2 DRAW TREASURE\n");
			printf("cardAdventurer() INFO: Does NOT ADD CORRECT # of Treasure Cards\n");
			failTests += 1;
		}
	}
	else
	{
		//if Adventure card was not properly discarded, check is handcount has 1 extra
		if (before.handCount[currentPlayer] != after->handCount[currentPlayer] + 1)
		{
			//FAILED: +2 Draw
			printf("cardAdventurer() FAIL: +2 DRAW TREASURE\n");
			printf("cardAdventurer() INFO: Does NOT ADD CORRECT # of Treasure Cards\n");
			failTests += 1;
		}
	}

	printf("Fail NUM: %d\n", failTests);

	return failTests;
}

int main()
{
	int n;
	int j;
	int numTests = 4;
	int gameIterations = 10; //change for the number of test games
	struct gameState testGame;

	//display testing message for cardTest2
	printf("----------------------------------------\n");
	printf("FUNCTION cardAdventurer() BEING TESTED...\n");
	printf("RANDOM TESTS...randomtestadventurer.c\n\n");

	//this is initializing stream for random number generation
	SelectStream(3);
	PutSeed(3);

	for (n = 1; n <= gameIterations; n++)
	{
		int outCome = 0;

		j = floor(Random() * MAX_PLAYERS);
		testGame.whoseTurn = j;
		testGame.deckCount[j] = floor(Random() * MAX_DECK / 3);
		testGame.discardCount[j] = floor(Random() * MAX_DECK / 3);
		testGame.handCount[j] = floor(Random() * MAX_HAND / 3);
		testGame.playedCardCount = floor(Random() * 5);

		outCome = testCardAdventurer(j, &testGame);

		if (outCome == 0)
		{
			printf("ALL TESTS PASSED\n");
		}
		else
		{
			printf("TEST #%d: cardAdventurer() FAILED %d out of %d TESTS\n\n", n, outCome, numTests);
		}
	}
	return 0;
}