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
	//what adventurer is supposed to do
	int drawnCard;
	int coinCard = 0;

	while (coinCard < 2)
	{
		if (pre.deckCount[player]< 1)
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
	printf("***IN FUNCTION****\n ___PRE___\n handcount: %d, deckcount: %d, discardcount: %d\n", pre.handCount[player], pre.deckCount[player], pre.discardCount[player]);
	printf("___POST___\n handcount: %d, deckcount: %d, discardcount: %d\n", post->handCount[player], post->deckCount[player], post->discardCount[player]);
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
				if(post->hand[player][post->handCount[player]-1] == copper || post->hand[player][post->handCount[player]-1] == silver || post->hand[player][post->handCount[player]-1] == gold)
				{
					if (post->hand[player][post->handCount[player]-2] == copper || post->hand[player][post->handCount[player]-2] == silver || post->hand[player][post->handCount[player]-2] == gold)
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
};

int main()
{
	//set up game
	int max_hand = 500;
	int max_deck = 500; 
	int i, j, handIndex, p, randNum;
	int NUM_PLAYERS= 2;
	int numCards = 17;
	int seed = 9999;
	srand(time(NULL));
	//struct gameState G = malloc(sizeof(struct gameState));
	struct gameState G;
	int kingdomcards[10] = {adventurer, council_room, feast, gardens, 
		mine, remodel, smithy, minion, baron, sea_hag};
	int gameCards[17] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, minion, baron, sea_hag, copper, silver, gold, estate, duchy, province, curse};

	for ( i = 0; i < 20; i++)
	{
		printf("\n\n************** test iteration %d **************\n", i);
		initializeGame(NUM_PLAYERS, kingdomcards, seed, &G);
		
		//randomize player turn, deck, hand, and discard count
		p = rand() %(NUM_PLAYERS+1);
		G.deckCount[p] = rand() %(max_deck/2);
		G.discardCount[p] = rand() %(max_deck/2);
		G.handCount[p] = rand() %(max_hand/2);
		
		//printf("p = %d, deckCount = %d, discardCount = %d, handCount = %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p]);
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
		
		//print pre-test stats
		printf(" - PRE -\n Player: %d\n deck count: %d	discard count: %d	hand count: %d\n adventurer in hand index: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p], handIndex);
		//run test
		int test = checkAdventurer(p, &G);
		switch(test)
		{
			case 0:
				{printf("test PASSED\n");}					
			case 1: 
				{printf("***** FAILED ***** second to last card in hand is not a coin card\n");}
			case 2: 
				{printf("***** FAILED ***** last card in hand is not a coin card\n");}
			case 3:
				{printf("***** FAILED ***** deck count is wrong\n");}
			case 4:
				{printf("***** FAILED ****** discard count is wrong\n");}
			case 5:
				{printf("***** FAILED ***** hand count is wrong\n");}
		}//end switch
		
		// print post-test game stats
		printf(" - POST -\n Player: %d\n deck count: %d		discard count: %d	hand count: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p]);
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
};
