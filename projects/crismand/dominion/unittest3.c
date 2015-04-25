/*
************************************
This is a unit test for the method isGameOver() from dominion.c  

************************************
*/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void testGO(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testGO(G1, G2);
	
    return 0;
}

void testGO(struct gameState *G1, struct gameState *G2){
	
	printf("\n*********************\n");
	printf("Testing isGameOver() method\n");
	printf("*********************\n\n");	
		
	//Test to make sure the conditions are not true at the onset.
	if(isGameOver(G1) == 0){
		printf("Test Passed, Game 1 was just initialized, it shouldn't be over. \n");
	} else {
		printf("Test Failed, Game 1 should not be over. \n");
	}
	
	if(isGameOver(G2) == 0){
		printf("Test Passed, Game 2 was just initialized, it shouldn't be over. \n");
	} else {
		printf("Test Failed, Game 2 should not be over. \n");
	}
	
	//Set provinces to 0 for Game 1
	G1->supplyCount[province] = 0;
	
	if(isGameOver(G1) == 1){
		printf("Test Passed, Game 1 has no more provinces. \n");
	} else {
		printf("Test Failed, Game 1 has no more provinces. \n");
	}
		
	//Set provinces to -1 for Game 1
	G1->supplyCount[province] = -1;	
	if(isGameOver(G1) == 1){
		printf("Test Passed, Game 1 has an invalid number of provinces. \n");
	} else {
		printf("Test Failed, Game 1 has an invalid number of provinces. \n");
	}
	
	//Set number of some other supply piles to 0
	G2->supplyCount[duchy] = 0;
	G2->supplyCount[estate] = 0;
	G2->supplyCount[curse] = 0;
	
	if(isGameOver(G2) == 1){
		printf("Test Passed, Game 2 has three piles depleted. \n");
	} else {
		printf("Test Failed, Game 2 has three piles depleted. \n");
	}
	
	//Set the third depleted pile to be a kingdom card.
	G2->supplyCount[curse] = 10;
	G2->supplyCount[gardens] = 0;
	if(isGameOver(G2) == 1){
		printf("Test Passed, Game 2 has three piles depleted. \n");
	} else {
		printf("Test Failed, Game 2 has three piles depleted. \n");
	}
	
	//Set the third depleted pile to be a kingdom card that isn't in the game.
	G2->supplyCount[gardens] = 10;
	G2->supplyCount[feast] = 0;
	if(isGameOver(G2) == 0){
		printf("Test Passed, Game 2 One of the piles that was depleted isn't in play. \n");
	} else {
		printf("Test Failed, Game 2 One of the piles that was depleted isn't in play. \n");
	}
	printf("\n");	
	return;
}