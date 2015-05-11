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
	
	//testing smithy fucntion
	int r = smithy(player, post, handpos);
	
	//What smithy function is supposed to do.
	int k;
	for( k = 0; k < 3; k++)
	{
		drawCard(player,&pre);
	}
	discardCard(handpos, player, &pre, 0)

	//Check if the two gameStates are the same
	if(pre.discardCount[player] == post->discardCount[p])
	{
		if(pre.handCount[player] == post->handCOunt[player])
		{
			return 0;
		}
	}
	return -1;

}


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
	struct gameState G;
	int kingdomcards[10] = {adventurer, council_room, feast, gardens, 
		mine, remodel, smithy, minion, baron, sea_hag};
	int gameCards[17] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, minion, baron, sea_hag, copper, silver, gold, estate, duchy, province, curse};


	for ( i = 0; i < 20; i++)
	{
		printf("\n\n************** test iteration %d **************\n", i+1);
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
		//print pre-test stats
		printf(" - PRE -\n Player: %d\n deck count: %d	discard count: %d	hand count: %d\n smithy in hand index: %d\n", p, G.deckCount[p], G.discardCount[p], G.handCount[p], handIndex);
		
		int test = checkSmithy(p, &G, 0);
		if (test != 0 )
		{
			printf("checkSmithy() FAILED\n");
		}
		else{printf("checkSmithy() PASSED\n");}
	}
	return 0;
}
