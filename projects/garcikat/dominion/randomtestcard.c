//testing smihty card effect
#include "dominion.c"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

int checkSmithy(int player, struct gameState *post, int handpos)
{
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	//testing smithy function
	int r = test_smithyCard(player, post, handpos);
	int drawnCardCount = pre.deckCount[player] - post->deckCount[player];
	
	if( post->deckCount[player] == (pre.deckCount[player]-3))
	{
		if( post->handCount[player] == (pre.handCount[player]+2))
		{
			if( post->playedCardCount == (pre.playedCardCount+1))
			{	//test passed
				printf("test PASSED\n");
				return drawnCardCount;
			}
			else//play card count incorrect
			{
				printf("***** FAILED TEST ***** played card count incorrect\n");
				return drawnCardCount;
			}
		}
		else//hand count is incorrect
		{
			printf("*****FAILED TEST ***** hand count incorrect\n");
			return drawnCardCount;
		}
	}
	else//deck count is incorrect
	{
		printf("***** FAILED TEST ***** deck count incorrect\n");
		return drawnCardCount;
	}			
};

int main()
{
	//set up game
	int max_hand = 500;
	int max_deck = 500; 
	int i, j, handIndex, p, randNum, preDeck, preHand, postDeck, postHand;
	int NUM_PLAYERS= 2;
	int numCards = 17;
	int seed = 9999;
	srand(time(NULL));
	struct gameState G;
	int kingdomcards[10] = {adventurer, council_room, feast, gardens, 
		mine, remodel, smithy, minion, baron, sea_hag};
	int gameCards[17] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, minion, baron, sea_hag, copper, silver, gold, estate, duchy, province, curse};


	for ( i = 0; i < 100; i++)
	{
		printf("\n\n-------------------- Smithy Card Test Iteration %d --------------------\n", i+1);
		initializeGame(NUM_PLAYERS, kingdomcards, seed, &G);
		
		//randomize player turn, deck, hand, and discard count
		p = rand() %(NUM_PLAYERS+1);
		G.deckCount[p] = rand() %(max_deck/2);
		G.discardCount[p] = rand() %(max_deck/2);
		G.handCount[p] = rand() %(max_hand/2);
		
		//randomize deck, discard and hand piles
		for ( j = 0; j < G.deckCount[p]; j++)
		{
			randNum = rand() %numCards;
			G.deck[p][j] = gameCards[randNum];
		}
		for ( j = 0; j < G.discardCount[p]; j++)
		{
			randNum = rand() %numCards;
			G.discard[p][j] = gameCards[randNum];
		}
		for ( j = 0; j < G.handCount[p]; j++)
		{
			randNum = rand() %numCards;
			G.hand[p][j] = gameCards[randNum];
		}
		//inserting smithy card into random hand index
		handIndex = rand() %(G.handCount[p]);
		G.hand[p][handIndex] = smithy;
		
		//saving pre-test stats
		preDeck = G.deckCount[p];
		preHand = G.handCount[p];
		
		//print pre-test stats
		printf(" ____PRE____\n Player: %d\n deck count: %d		discard count: %d	hand count: %d\n smithy in hand index: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p], handIndex);
		
		//run test
		printf("\n			TEST RESULTS		\n");
		int test = checkSmithy(p, &G, 0);

		//calculate post-test stats
		postDeck = preDeck - test;
		postHand = preHand+2;
		
		// print post-test game stats
		printf("\n ____POST____\n deck count: %d 	card drawn count: %d 	played card count: %d	hand count: %d\n", G.deckCount[p], test, G.playedCardCount, G.handCount[p]);
		printf("\n\nExpected Results:\n deck count: %d 	cards drawn count: 3 	played card count: 1	hand count: %d\n", postDeck, postHand);
	}
	return 0;
}
