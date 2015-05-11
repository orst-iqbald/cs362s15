/* Jason MacManiman
 * Assignment 4
 * Write a random tester for 2 cards, one of which
 * must be adventurer. This random tester will be for
 * the 'smithy' card.
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

int main(int argc, char** argv) {
	struct gameState g;
	int i = 0;
	int k = 0;
	int preTreasure = 0;
	int postTreasure = 0;
	int preHand = 0;
	int postHand = 0;
	int handPos = 0;
	int numPlayers = 0;
	int currPlayer = 0;
	int seed = 0;
	int Terror = 0;
	int Herror = 0;

	srand(time(NULL));

	int actioncards[10] = { adventurer, smithy, cutpurse, outpost, gardens, village, sea_hag, mine, minion, embargo };
	
	for(k = 0; k < 1000; k++) {
		//for each iteration of the test, the number of treasure
		//cards and cards in hand will be reset to 0, and the 
		//gamestate initialized.
		
		preTreasure = 0;
		postTreasure = 0;
		preHand = 0;
		postHand = 0;

		seed = (rand()%65535);
		numPlayers = ((rand()%3)+2);
		initializeGame(numPlayers, actioncards, seed, &g);

		currPlayer = ((rand()%numPlayers));

	printf("Players: %d\n", numPlayers);
	
	for(i = 0; i < g.handCount[currPlayer]; i++) {
		if(g.hand[currPlayer][i] == copper ||
			g.hand[currPlayer][i] == silver ||
			g.hand[currPlayer][i] == gold)
			{
				preTreasure++;
			} else {
				handPos = i;
			}
	
			preHand = i+1;
	}

	printf("Treasures PRE: %d\n", preTreasure);
	printf("Cards PRE: %d\n", preHand);

	// play the smithy card and then check the number of treasure cards
	// and cards-in-hand again, making sure they change as expected.
	playSmithyCard(&g, currPlayer, handPos);

	for(i = 0; i < g.handCount[currPlayer]; i++) {
	if(g.hand[currPlayer][i] == copper ||
		g.hand[currPlayer][i] == silver ||
		g.hand[currPlayer][i] == gold)
		{
			postTreasure++;
		} else {
			handPos = i;
		}
	
		postHand = i+1;
	}

	printf("Treasures POST: %d\n", postTreasure);
	printf("Cards POST: %d\n", postHand);

	//check if the player has correctly ended up with 2 more treasure cards
	if(preTreasure > postTreasure) {
		printf("ERROR: preTreasures > postTreasures!\n");
		Terror++;
	}

	//check if the player has correctly ended up with 2 more cards
	// originally checked for +3, but had forgotten about the discard 
	if((preHand + 2) != postHand) {
		printf("ERROR: preHand+3 != postHand!\n");
		Herror++;
	}

	printf("______________________________________________\n\n");
	}
	
	printf("***END OF SMITHY TEST***\n");
	printf("Errors in Treasure Allocation: %d\n", Terror);
	printf("Errors in Card Allocation: %d\n", Herror);
	printf("*************************************\n\n");
	return 0;

}
