/*
************************************
This is a unit test for the method cardAdventurer() from dominion.c  
cardAdventurer stands for Play Adventurer

************************************
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void testAdventurer(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testAdventurer(G1, G2);
	
    return 0;
}

void testAdventurer(struct gameState *G1, struct gameState *G2){
	
	int res1;
	int d1, d2;
	int h1, h2;
	int b1, c1;
			
	printf("\n*********************\n");
	printf("Testing Adventurer card effect\n");
	printf("*********************\n\n");	
	
	//Record number of cards in initial discard (should be 0)
	d1 = G1->discardCount[0];
	d2 = G2->discardCount[0];
	
	//Record number of coins and buys
	b1 = G1->numBuys;
	c1 = G1->coins;
	
	//Add an adventurer card to Payer 1's hand in two games	
	G1->hand[0][G1->handCount[0]] = adventurer;
	G1->handCount[0]++;
	
	G2->hand[0][G2->handCount[0]] = adventurer;
	G2->handCount[0]++;
	
	//Record number of cards in each hand (should be 6)
	h1 = G1->handCount[0];
	h2 = G2->handCount[0];

	//Play the smithy in Game 1, Player 1
	res1 = cardAdventurer(G1->whoseTurn, G1);
	
	//Test to see if 2 cards were added to the hand
	if(G1->handCount[0] == (h1 + 2)){
		printf("Test Passed, 2 cards were added to the hand. \n");
	} else {
		printf("Test Failed, something else happened; 2 cards were not added to the hand. \n");
	}
	
	//Test to see if both cards that were added to the hand are treasure cards
	if(G1->hand[0][G1->handCount[0] - 2] == copper || G1->hand[0][G1->handCount[0] - 2] == silver || G1->hand[0][G1->handCount[0] - 2] == gold){
		printf("Test Passed, first card added was a treasure card. \n");
	} else {
		printf("Test Failed, first card added was not a treasure card. \n");
	}
	
	if(G1->hand[0][G1->handCount[0] - 1] == copper || G1->hand[0][G1->handCount[0] - 1] == silver || G1->hand[0][G1->handCount[0] - 1] == gold){
		printf("Test Passed, second card added was a treasure card. \n");
	} else {
		printf("Test Failed, second card added was not a treasure card. \n");
	}
	
	//Test to see if other cards were discarded.	
	if(G1->discardCount[0] > (d1)){
		printf("Test Passed, At least 1 card was added to the discard. \n");
	} else {
		printf("Test Failed, something else happened; At least 1 card was not added to the discard. \n");
	}
	
	//Test to see if number of coins was altered (shouldn't be)
	if(G1->coins == c1){
		printf("Test Passed, Coins were not altered. \n");
	} else {
		printf("Test Failed, Number of coins changed after adventurer was played.  \n");
	}

	//Test to see if number of buys was altered (shouldn't be)
	if(G1->numBuys == b1){
		printf("Test Passed, Buys were not altered. \n");
	} else {
		printf("Test Failed, Number of buys changed after adventurer was played.  \n");
	}
	
	//Test to see if the deck still had the same total number of cards as the Game 2 Player 1 deck.
	if(G1->deckCount[0] == G2->deckCount[0]){
		printf("Test Passed, Player 1 from both games have the same size deck. \n");
	} else {
		printf("Test Failed, something else happened; Player 1 from both games do not have the same size deck. \n");
	}
	printf("\n");	
	return;
}