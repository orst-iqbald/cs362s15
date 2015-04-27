/*
************************************
This is a unit test for the method pFeast() from dominion.c  
pFeast stands for Play Feast

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

void testFeast(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testFeast(G1, G2);
	
    return 0;
}

void testFeast(struct gameState *G1, struct gameState *G2){
	
	int res1;
	int d1, d2;
	int h1, h2;
	int b1, c1;
				
	printf("\n*********************\n");
	printf("Testing Feast card effect\n");
	printf("*********************\n\n");	
	
	//Set smithy to 0 so we can try to use feast to get one with the feast card and test to make sure it fails
	G1->supplyCount[smithy] = 0;
	
	//Record number of cards in initial discard (should be 0)
	d1 = G1->discardCount[0];
	d2 = G2->discardCount[0];
	
	//Record number of coins and buys
	b1 = G1->numBuys;
	c1 = G1->coins;
	
	//Add a feast card to Payer 1's hand in two games	
	G1->hand[0][G1->handCount[0]] = feast;
	G1->handCount[0]++;
	
	G2->hand[0][G2->handCount[0]] = feast;
	G2->handCount[0]++;
	
	//Record number of cards in each hand (should be 6)
	h1 = G1->handCount[0];
	h2 = G2->handCount[0];

	//Play the feast card, try to buy a card that should cost too much in Game 1, Player 1
	res1 = pFeast(G1, gold, G1->hand[0][h1 - 1]);
	if(G1->handCount[0] > h1){
		if(G1->hand[0][h1] == gold){
			printf("Test Failed, Allowed to buy a card that is too much value. \n");
		} else {
			printf("Test Failed, Something strange happened, we have an extra card, but it isn't what we tried to buy. \n Extra Card is: %i\n", G1->hand[0][G1->handCount[0] - 1]);
		}
	} else {
		printf("Test Passed, no cards were added to the hand when we tried to buy a gold. \n");
	}
	
	//Play the feast card, try to buy a card that should cost too much in Game 1, Player 1
	res1 = pFeast(G1, province, G1->hand[0][h1 - 1]);
	if(G1->handCount[0] > h1){
		if(G1->hand[0][h1] == province){
			printf("Test Failed, Allowed to buy a card that is too much value. \n");
		} else {
			printf("Test Failed, Something strange happened, we have an extra card, but it isn't what we tried to buy. \n Extra Card is: %i\n", G1->hand[0][G1->handCount[0] - 1]);
		}
	} else {
		printf("Test Passed, no cards were added to the hand when we tried to buy a province. \n");
	}	

	//Play the feast card, try to buy the smithy card that should be depleted in Game 1, Player 1
	res1 = pFeast(G1, smithy, G1->hand[0][h1 - 1]);
	if(G1->handCount[0] > h1){
		if(G1->hand[0][h1] == smithy){
			printf("Test Failed, Allowed to buy a card that is too much value. \n");
		} else {
			printf("Test Failed, Something strange happened, we have an extra card, but it isn't what we tried to buy. \n Extra Card is: %i\n", G1->hand[0][G1->handCount[0] - 1]);
		}
	} else {
		printf("Test Passed, no cards were added to the hand when we tried to buy from the depleted smithys. \n");
	}		
	
	//Play the feast in Game 1, Player 1
	res1 = pFeast(G1, village, G1->hand[0][h1 - 1]);
	
	//Test to see if village card was added to the discard
	if(G1->discard[0][d1] == village){
		printf("Test Passed, Village card was added to the discard. \n");
	} else {
		printf("Test Failed, Village not added to discard, top card is %i. \n", G1->discard[0][d1]);
	}
	
	//Test to make sure the hand is one card fewer.
	if(G1->handCount[0] == (h1 - 1)){
		printf("Test Passed, Hand is decremented by one card. \n");
	} else {
		printf("Test Failed, Hand was not decremented, or something else happened. \n");
	}	
	
	//Test to see if discard pile remains the same.	
	if(G1->discardCount[0] == (d1 + 1)){
		printf("Test Passed, Discard pile is still 0. \n");
	} else {
		printf("Test Failed, something else happened; At least 1 card was added to the discard. \n");
	}
	
	//Test to see if number of coins was altered (shouldn't be)
	if(G1->coins == c1){
		printf("Test Passed, Coins were not altered. \n");
	} else {
		printf("Test Failed, Number of coins changed after feast was played.  \n");
	}

	//Test to see if number of buys was altered (shouldn't be)
	if(G1->numBuys == b1){
		printf("Test Passed, Buys were not altered. \n");
	} else {
		printf("Test Failed, Number of buys changed after feast was played.  \n");
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