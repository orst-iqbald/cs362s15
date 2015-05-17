/*
************************************
This is a unit test for the method effectCouncilRoom() from dominion.c  
effectCouncilRoom stands for Play Council Room

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

void testCR(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, feast, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testCR(G1, G2);
	
    return 0;
}

void testCR(struct gameState *G1, struct gameState *G2){
	
	int res1;
	int d1, d2;
	int h1, h2, p1, p2;
	int b1, c1;
				
	printf("\n*********************\n");
	printf("Testing Council Room card effect\n");
	printf("*********************\n\n");	
	
	//Record number of cards in initial discard (should be 0)
	d1 = G1->discardCount[0];
	d2 = G2->discardCount[0];
	
	//Record number of coins and buys
	b1 = G1->numBuys;
	c1 = G1->coins;
	
	//Add a council room card to Payer 1's hand in two games	
	G1->hand[0][G1->handCount[0]] = council_room;
	G1->handCount[0]++;
	
	G2->hand[0][G2->handCount[0]] = council_room;
	G2->handCount[0]++;
	
	//Record number of cards in each hand (should be 6)
	h1 = G1->handCount[0];
	h2 = G2->handCount[0];
	
	//Record number of cards in other players hands (not sure what to expect, should be 5).
	p1 = G1->handCount[1];
	p2 = G2->handCount[1];

	//Play the feast in Game 1, Player 1
	res1 = effectCouncilRoom(G1, G1->hand[0][h1 - 1]);
	
	//Test to see if 4 cards were added to the hand, but council room should have been discarded.  Net +3 cards.
	if(G1->handCount[0] == (h1 + 3)){
		printf("Test Passed, hand has 3 additional cards \n");
	} else {
		printf("Test Failed, something else happened; Hand does not have 3 additional cards. \n");
	}
	
	//Test to see if the council room card was added to the discard.	
	if(G1->discardCount[0] == (d1 + 1)){
		printf("Test Passed, 1 card was added to the discard. \n");
		if(G1->discard[0][d1] == council_room){
			printf("Test Passed, Top of discard pile is Council Room card. \n");
		} else {
			printf("Test Failed, Top card in discard pile is not Council Room card, it is: %i. \n", G1->discard[0][d1]);
		}
	} else {
		printf("Test Failed, something else happened; 1 card was not added to the discard. \n");
	}
	
	//Test to see if 1 cards were added to other player's hand.
	if(G1->handCount[1] == (p1 + 1)){
		printf("Test Passed, other player's hand has 1 additional card. \n");
	} else {
		printf("Test Failed, something else happened; other player's hand does not have 1 additional card. \n");
	}
	
	//Test to see if number of coins was altered (shouldn't be)
	if(G1->coins == c1){
		printf("Test Passed, Coins were not altered. \n");
	} else {
		printf("Test Failed, Number of coins changed after council room was played.  \n");
	}

	//Test to see if number of buys was altered (should be increased by 1)
	if(G1->numBuys == (b1 + 1)){
		printf("Test Passed, 1 Buy was added. \n");
	} else {
		printf("Test Failed, Number of buys not increased by one.  \n");
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