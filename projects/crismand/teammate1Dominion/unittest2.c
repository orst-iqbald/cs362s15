/*
************************************
This is a unit test for the method endTurn() from dominion.c  

************************************
*/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


void ET(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    ET(G1, G2);
	
    return 0;
}

void ET(struct gameState *G1, struct gameState *G2){
	
	int res;
	int curr1, curr2, hand1, discard1;
	
	curr1 = whoseTurn(G1);
	curr2 = whoseTurn(G2);
	G1->coins = 6;
	G1->numBuys = 10;	
	hand1 = G1->handCount[curr1];
	discard1 = G1->discardCount[curr1];
	
	printf("\n*********************\n");
	printf("Testing endTurn() method\n");
	printf("*********************\n\n");	
	
	res = endTurn(G1);	
	
	//Test to make sure turn was passed
	if(curr1 == whoseTurn(G1)){
		printf("Test Failed, Turn did not pass to next player. \n");
	} else {
		printf("Test Passed, turn passed to another player. \n");
	}
	
	//Test to make sure coins were reset.
	if(G1->coins > 0){
		printf("Test Failed, Coins were not reset. Coins: %i.\n", G1->coins);
	} else {
		printf("Test Passed, Coins were reset to 0.\n");
	}
	
	//Test to make sure buys were reset
	if(G1->numBuys > 1){
		printf("Test Failed, Buys were not reset. Buys: %i.\n", G1->numBuys);
	} else {
		printf("Test Passed, Buys were reset to 1.\n");
	}
	
	//Test to see if hand was discarded
	if(G1->discardCount[curr1] == (hand1 + discard1)){
		printf("Test Passed, Hand was discarded.\n");
	} else {
		printf("Test Failed, something else happened to hand.\n");
	}
	
	
	//Test to see if player's turn is reset to 0 if forced out of range.
	G2->whoseTurn = 5;
	res = endTurn(G2);
	if(res != 0){
		printf("Turn failed to end...\n");
	}
	if(whoseTurn(G2) != 0){
		printf("Test Failed, player went out of range.\n");
	} else {
		printf("Test Passed, player reset to 0 after being out of range.\n");
	}
	
	printf("\n");	
	return;
}