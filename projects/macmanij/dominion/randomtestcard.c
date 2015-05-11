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
	int preTreasure = 0;
	int postTreasure = 0;
	int preHand = 0;
	int postHand = 0;
	int handPos = 0;
	int numPlayers = 0;
	int currPlayer = 0;
	int seed = 0;

	srand(time(NULL));

	int actioncards[10] = { adventurer, smithy, cutpurse, outpost, gardens, village, sea_hag, mine, minion, embargo };
	
	for(i = 0; i < 100; i++) {
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

	

	}
	
	return 0;

}
