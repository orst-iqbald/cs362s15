//testing adventure card
#include "dominion.c"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <rngs.h>

int checkAdventurer(int player, struct gameState *post)
{	
	int [] temphand;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r = adventurer(player, *post, temphand);
	//what adventurer is supposed to do
	int drawnCard;
	int coinCard = 0;

	while (coinCard < 2)
	{
		if (pre->deckCount[player]< 1)
		{
			shuffle(player, &pre);
		}
		pre.hand[player][pre.handCount[player]] = pre.deck[player][pre.deckCount[player]-1];
		pre.handCount[player]++;
		pre.deckCount[player]--;
		drawnCard = pre.hand[player][pre.handCount[player]-1];
		if ( drawnCard == copper || drawnCard == silver || drawnCard || gold)
		{
			coinCard++;
		}
		else
		{
			pre.discard[player][pre.discardCount[player]]= drawnCard;
			pre.discardCount[player]++;
			pre.handCount[player]--;
		}
	}
	//now check if post and pre have the same results
	//1: same hand count
	if(pre.handCount[player] == post->handCount[player])
	{
		//2: same discard pile count
		if(pre.discardCount[player] == post->discardCount[player])
		{
			//same deck count
			if(pre.deckCount[player] == post->deckCount[player])
			{
				//4: last two cards in hand are coin cards
				if(post->hand[p][post->handCount[p]-1] == copper || post->hand[p][post->handCount[p]-1] == silver || post->hand[p][post->handCount[p]-1] == gold)
				{
					if (post->hand[p][post->handCount[p]-2] == copper || post->hand[p][post->handCount[p]-2] == silver || post->hand[p][post->handCount[p]-2] == gold)
					{
						return 0;
					}
					else //second to last card in hand is not a coin card
					{
						return 1;
					}
				}
				else // last card in hand is not a coin card
				{
					return 2;
				}
			}
			else // deck count is wrong
			{
				return 3;
			}
		}
		else //discard count is wrong
		{
			return 4;
		}
	}
	else // hand count is wrong
	{
		return 5;
	}
}
int main()
{
	//set up game
	int i, j, handIndex, p;
	int NUM_PLAYERS= 2;
	int numCards = 17;
	int seed 9999;
	struct game G;
	int kingdomcards[10] = {adventurer, council_room, feast, gardens, 
		mine, remodel, smithy, minion, baron, seahag};
	int gameCards[numCards] = {adventurer, council_room, feast, gardens, mine, 
		remodel, smithy, minion, baron, seahag, copper, silver, gold, estate, duchy, province, curse};
	SelectStream(2);
	PutSeed(seed);

	for ( i = 0; i < 100; i++)
	{
		printf("************** test iteration %d **************\n", i);
		initializeGame(NUM_PLAYERS, kingdomcards, seed, &G);
		
		//randomize player turn, deck, hand, and discard count
		p = floor(Random() * NUM_PLAYERS);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);

		//randomize deck, discard and hand piles
		for ( j = 0; j < G.deckCount[p]; j++)
		{
			G.deck[p][j] = gameCards[floor(Random() * numCards)];
		}
		for ( j = 0; j < G.discardCount[p]; j++)
		{
			G.discard[p][j] = gameCards[floor(Random() * numCards)];
		}
		for ( j = 0; j < G.handCount[p]l j++)
		{
			G.hand[p][j] = gameCards[floor(Random() * numCards)];
		}
		
		//inserting adventurer card into random hand index
		handIndex = floor(Random() * G.handCount[p]);
		G.hand[p][handIndex] = adventurer;
		
		//print pre-test stats
		printf(" - PRE -\n
				Player: %d\n
				deck count: %d 		discard count: %d 	hand count: %d\n
				adventurer in hand index: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p], handIndex);
		
		//run test
		int test = checkAdventurer(player, &G);
		switch(test)
		{
			case 0:
				printf("test PASSED\n");					
			case 1: 
				printf("***** FAILED ***** second to last card in hand is not a coin card\n");
			case 2: 
				printf("***** FAILED ***** last card in hand is not a coin card\n");
			case 3:
				printf("***** FAILED ***** deck count is wrong\n");
			case 4:
				printf("***** FAILED ****** discard count is wrong\n");
			case 5:
				printf("***** FAILED ***** hand count is wrong\n");
		}//end switch
		
		// print post-test game stats
		printf(" - POST -\n
				Player: %d\n
				deck count: %d 		discard count: %d 	hand count: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p]);
		/*if( test != 0)
		{
			printf("***** FAILED ***** checkAdventurer()\n");
		}
		else
		{
			printf("PASSED checkAdventurer()\n");
		}*/
		
	}//end for
	return 0;

}
