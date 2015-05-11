//testing adventure card
#include "dominion.c"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

int checkAdventurer(int player, struct gameState *post)
{	
	int temphand[MAX_HAND];
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r = test_adventurerCard(player, post, temphand);
	int diffDiscardCount = post->discardCount[player] - pre.discardCount[player];
	int drawnCardCount = diffDiscardCount+2;
	
	if( post->handCount[player] == (pre.handCount[player]+2))
	{
		if( post->deckCount[player] == (pre.deckCount[player]- drawnCardCount))
		{
			if(post->hand[player][post->handCount[player]-1] == copper || post->hand[player][post->handCount[player]-1] == silver || post->hand[player][post->handCount[player]-1] == gold)
			{
				if(post->hand[player][post->handCount[player]-2] == copper || post->hand[player][post->handCount[player]-2] == silver || post->hand[player][post->handCount[player]-2] == gold)
				{
					printf("test PASSED\n");
					return drawnCardCount;
				}
				else
				{
					printf("******* FAILED ******* second to last card in hand is not a coin card\n");
					return drawnCardCount;
				}
			}
			else
			{
				printf("******* FAILED ******* last card in hand is not a coin card\n");
				return drawnCardCount;
			}
		}
		else
		{
			printf("******* FAILED ******* deck count is wrong\n");
			return drawnCardCount;
		}
	}
	else
	{
		printf("******* FAILED ******* hand count is wrong\n");
		return drawnCardCount;
	}
};	

int main()
{
	//set up game
	int max_hand = 500;
	int max_deck = 500; 
	int i, j, handIndex, p, randNum, preDeck, preDiscard, preHand, postDeck, postDiscard, postHand;
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
		printf("\n\n-------------------- Adventurer Card Test Iteration %d --------------------\n", i+1);
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
		
		//inserting adventurer card into random hand index
		handIndex = rand() %(G.handCount[p]);
		G.hand[p][handIndex] = adventurer;
		
		//saving pre-test stats
		preDeck = G.deckCount[p];
		preDiscard = G.discardCount[p];
		preHand = G.handCount[p];
		
		//print pre-test stats
		printf(" _____PRE_____\n Player: %d\n deck count: %d 	discard count: %d	hand count: %d\n adventurer in hand index: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p], handIndex);
		
		//run test
		printf("\n			TEST RESULTS		\n");
		int test = checkAdventurer(p, &G);
		
		//calculate post-test stats
		postDeck = preDeck - test;
		postDiscard = preDiscard + (test-2);
		postHand = preHand+2;
		
		//print post stats
		printf("\n  _____POST_____\n deck count: %d 	cards drawn: %d		discard count: %d	hand count: %d\n", G.deckCount[p], test, G.discardCount[p], G.handCount[p]);
		printf("\n\nExpected Results:\n deck count: %d 	cards drawn: %d		discard count: %d	hand count: %d\n", postDeck, test, postDiscard, postHand);
	}//end for
	return 0;
};
