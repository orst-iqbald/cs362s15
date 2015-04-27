/*
************************************
This is a unit test for the method pSmithy() from dominion.c  
pSmithy stands for Play Smithy

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

void testSmithy(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testSmithy(G1, G2);
	
    return 0;
}

void testSmithy(struct gameState *G1, struct gameState *G2){
	
	int res1;
	int d1, d2;
	int h1, h2;
		
	printf("\n*********************\n");
	printf("Testing Smithy card effect\n");
	printf("*********************\n\n");	
	
	//Record number of cards in initial discard (should be 0)
	d1 = G1->discardCount[0];
	d2 = G2->discardCount[0];
	
	//Add a smithy card to Payer 1's hand in two games	
	G1->hand[0][G1->handCount[0]] = smithy;
	G1->handCount[0]++;
	
	G2->hand[0][G2->handCount[0]] = smithy;
	G2->handCount[0]++;
	
	//Record number of cards in each hand (should be 6)
	h1 = G1->handCount[0];
	h2 = G2->handCount[0];

	//Play the smithy in Game 1, Player 1
	res1 = pSmithy(G1, G1->hand[0][h1 - 1]);
	
	//Test to see if 3 cards were added to the hand but smithy was also discarded, net +2
	if(G1->handCount[0] == (h1 + 2)){
		printf("Test Passed, hand has 2 additional cards \n");
	} else {
		printf("Test Failed, something else happened; Hand does not have 2 additional cards. \n");
	}
	
	//Test to see if the smithy card was added to the discard.	
	if(G1->discardCount[0] == (d1 + 1)){
		printf("Test Passed, 1 card was added to the discard. \n");
	} else {
		printf("Test Failed, something else happened; 1 card was not added to the discard. \n");
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