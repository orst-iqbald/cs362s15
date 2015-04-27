#define TESTFUNCTION "scoreFor()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
	
int main() {
    int i;
	int seedRandom = 1000;
    int numPlayers = 2;
	int handPos;
	int deckPos;
	int discardPos;
	int quantCurse;
	int quantEstate;
	int quantDuchy;
	int quantProvince;
	int quantGarden;
	int whichCard;
	int playerScore;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seedRandom, &G);
	
	for (i = 0; i < 12; i++)
	{
		if (i < 6)
			G.hand[0][i] = 5;
		G.deck[0][i] = 5;
	}

	printf("-------------------- Test: %s --------------------\n", TESTFUNCTION);

	G.handCount[0] = 6; //set 6 cards initially in hand
	G.deckCount[0] = 0;
	G.discardCount[0] = 0;
	whichCard = quantCurse = quantEstate = quantDuchy = quantProvince = quantGarden = 0;
	
	printf("Test cards in hand\n");
	for (i = 0; i < 4; i++)
	{
		assert (G.handCount[0] == 6);
		assert (G.deckCount[0] == 0);
		assert (G.discardCount[0] == 0);
		for (handPos = 0; handPos < 6; handPos++)
		{
			switch(G.hand[0][handPos])
			{
				case 0:
					quantCurse--;
					break;
				case 1: 
					quantEstate--;
					break;
				case 2: 
					quantDuchy--;
					break;
				case 3: 
					quantProvince--;
					break;
				case 10:
					quantGarden--;
					break;
				default:
					break;
			}
			
			switch(whichCard) 
			{
				case 0: 
					G.hand[0][handPos] = 0;
					quantCurse++;
					break;
				case 1: 
					G.hand[0][handPos] = 1;
					quantEstate++;
					break;
				case 2: 
					G.hand[0][handPos] = 2;
					quantDuchy++;
					break;
				case 3: 
					G.hand[0][handPos] = 3;
					quantProvince++;
					break;
				case 10:
					G.hand[0][handPos] = 10;
					quantGarden++;
					break;
				default: 
					break;
			}
			
			if (whichCard == 3)
				whichCard = 10;
			else if (whichCard == 10)
				whichCard = 0;
			else
				whichCard++;

			playerScore = scoreFor (0, &G);
			assert (playerScore >= -6);
			printf("Curse %d + Estate %d + Duchy %d + Province %d + Garden %d = Total %d, ", quantCurse, quantEstate, quantDuchy, quantProvince, quantGarden, playerScore);
			if (playerScore == quantEstate - quantCurse + (quantDuchy * 3) + (quantProvince * 6))
				printf("which is expected.\n");
			else
				printf("which is NOT expected.\n");
		}
	}
	
	for (i = 0; i < 6; i++)
		G.hand[0][i] = 5; 
	
	G.handCount[0] = 0;
	G.deckCount[0] = 12;
	G.discardCount[0] = 0;
	
	whichCard = quantCurse = quantEstate = quantDuchy = quantProvince = quantGarden = 0;
	
	printf("\nTest cards in deck\n");
	for (i = 0; i < 2; i++)
	{
		assert (G.handCount[0] == 0);
		assert (G.deckCount[0] == 12);
		assert (G.discardCount[0] == 0);
		for (deckPos = 0; deckPos < 12; deckPos++)
		{
			switch(G.deck[0][deckPos])
			{
				case 0:
					quantCurse--;
					break;
				case 1: 
					quantEstate--;
					break;
				case 2: 
					quantDuchy--;
					break;
				case 3: 
					quantProvince--;
					break;
				case 10:
					quantGarden--;
					break;
				default:
					break;
			}
			
			switch(whichCard) 
			{
				case 0: 
					G.deck[0][deckPos] = 0;
					quantCurse++;
					break;
				case 1: 
					G.deck[0][deckPos] = 1;
					quantEstate++;
					break;
				case 2: 
					G.deck[0][deckPos] = 2;
					quantDuchy++;
					break;
				case 3: 
					G.deck[0][deckPos] = 3;
					quantProvince++;
					break;
				case 10:
					G.deck[0][deckPos] = 10;
					quantGarden++;
					break;
				default: 
					break;
			}
			
			if (whichCard == 3)
				whichCard = 10;
			else if (whichCard == 10)
				whichCard = 0;
			else
				whichCard++;

			playerScore = scoreFor (0, &G);
			assert (playerScore >= -12);
			printf("Curse %d + Estate %d + Duchy %d + Province %d + Garden %d = %d Total, ", quantCurse, quantEstate, quantDuchy, quantProvince, quantGarden, playerScore);
			if (playerScore == quantEstate - quantCurse + (quantDuchy * 3) + (quantProvince * 6))
				printf("which is expected.\n");
			else
				printf("which is NOT expected.\n");
		}
	}
	
	for (i = 0; i < 12; i++)
	{
		G.deck[0][i] = 5;
		G.discard[0][i] = 5;
	}
	
	G.handCount[0] = 0;
	G.deckCount[0] = 0;
	G.discardCount[0] = 12;
	
	whichCard = quantCurse = quantEstate = quantDuchy = quantProvince = quantGarden = 0;
	
	printf("\nTest cards in discard\n");
	for (i = 0; i < 2; i++)
	{
		assert (G.handCount[0] == 0);
		assert (G.deckCount[0] == 0);
		assert (G.discardCount[0] == 12);
		for (discardPos = 0; discardPos < 12; discardPos++)
		{
			switch(G.discard[0][discardPos])
			{
				case 0:
					quantCurse--;
					break;
				case 1: 
					quantEstate--;
					break;
				case 2: 
					quantDuchy--;
					break;
				case 3: 
					quantProvince--;
					break;
				case 10:
					quantGarden--;
					break;
				default:
					break;
			}
			
			switch(whichCard) 
			{
				case 0: 
					G.discard[0][discardPos] = 0;
					quantCurse++;
					break;
				case 1: 
					G.discard[0][discardPos] = 1;
					quantEstate++;
					break;
				case 2: 
					G.discard[0][discardPos] = 2;
					quantDuchy++;
					break;
				case 3: 
					G.discard[0][discardPos] = 3;
					quantProvince++;
					break;
				case 10:
					G.discard[0][discardPos] = 10;
					quantGarden++;
					break;
				default: 
					break;
			}
			
			if (whichCard == 3)
				whichCard = 10;
			else if (whichCard == 10)
				whichCard = 0;
			else
				whichCard++;

			playerScore = scoreFor (0, &G);
			assert (playerScore >= -12);
			printf("Curse %d + Estate %d + Duchy %d + Province %d + Garden %d = %d Total, ", quantCurse, quantEstate, quantDuchy, quantProvince, quantGarden, playerScore);
			if (playerScore == quantEstate - quantCurse + (quantDuchy * 3) + (quantProvince * 6))
				printf("which is expected.\n");
			else
				printf("which is NOT expected.\n");
		}
	}
	
    printf("\n-------------------- Test: %s completed --------------------\n\n", TESTFUNCTION);

    return 0;
}