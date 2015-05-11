//regular includes
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>

//dominion includes
#include "dominion_helpers.h"
#include "dominion.h"
#include "interface.h"

int main(int argc, char** argv)
{
	struct gameState state;			//state of game
	int i;							//used in for loops
	int seed = 0;					//seed to initialize game
	int treasureCardsBefore = 0;	//number of treasure cards before adventurer card is played
	int treasureCardsAfter = 0;		//number of treasure cards after adventurer card is played
	int handCountBefore = 0;		//number of cards in hand before adventurer card is played
	int handCountAfter = 0;			//number of cards in hand after adventurer card is played
	int randPlayer;					//place of randomly selected player
	int errorBool = 0;				//boolean that determines whether an error has occured so the game seed can be printed
	int numberOfPlayers = 0;		//amount of players in game
	int handPosition = 0;			//position of card in hand

	srand(time(NULL));				//initialize random numbers

	int cards[10] = { mine, adventurer, village, minion, embargo, sea_hag, cutpurse, gardens, smithy, tribute };

	for (i = 0; i < 30; i++)
	{
		//initialize game
		seed = (rand() % 65535);
		numberOfPlayers = ((rand() % 3) + 2);
		initializeGame(numberOfPlayers, cards, seed, &state);

		//set card counts to 0
		treasureCardsBefore = 0;
		treasureCardsAfter = 0;
		handCountBefore = 0;
		handCountAfter = 0;

		//get random player
		randPlayer = ((rand() % numberOfPlayers));

		//show size of deck and # of players
		printf("Deck count: %d\n", state.deckCount[randPlayer]);
		printf("Player count: %d\n", numberOfPlayers);

		//get # of treasure cards and size of hand
		for (i = 0; i < state.handCount[randPlayer]; i++)
		{
			if (state.hand[randPlayer][i] == copper || state.hand[randPlayer][i] == silver || state.hand[randPlayer][i] == gold)
			{
				treasureCardsBefore++;
			}
			else
			{
				handPosition = i;
			}

			handCountBefore = i + 1;
		}

		//show number of cards before playing an adventurer card
		printf("Treasure cards before adventurer: %d\n", treasureCardsBefore);
		printf("Cards in hand before adventurer: %d\n", handCountBefore);

		//play an adventurer card
		adventurerCard(&state, handPosition, randPlayer);

		//get number of cards in hand and number of treasure cards after adventurer card is played
		for (i = 0; i < state.handCount[randPlayer]; i++)
		{
			if (state.hand[randPlayer][i] == copper || state.hand[randPlayer][i] == silver || state.hand[randPlayer][i] == gold)
			{
				treasureCardsAfter++;
				handCountAfter = i + 1;
			}
		}

		//show number of cards after playing an adventurer card
		printf("Treasure cards after adventrer: %d\n", treasureCardsAfter);
		printf("Cards in hand after adventurer: %d\n", handCountAfter);

		//treasure card count doesn't line up, show error message
		if (treasureCardsBefore + 2 != treasureCardsAfter)
		{
			printf("Number of treasure cards doesn't line up!\n");
			errorBool = 1;
			printf("Game seed = %d\n", seed);
		}

		//number of cards in hand doesn't line up, show error message
		if ((handCountBefore + 2) != handCountAfter)
		{
			printf("Number of cards in hand doesn't line up!\n");

			if (errorBool == 0)
			{
				printf("Game seed = %d\n", seed);
			}
		}

		//get ready for another entry
		printf("\n*********************************************\n\n");
	}

	return 0;
}