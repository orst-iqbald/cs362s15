/*
************************************
This is a unit test for the method shuffle() from dominion.c  

************************************
*/
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void testShuffle(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testShuffle(G1, G2);
	
    return 0;
}

void testShuffle(struct gameState *G1, struct gameState *G2){
	
	int res1, res2;
	int d1, d2, d3, d4;
	
	
	d1 = G1->deckCount[0];
	d2 = G1->deckCount[1];
	d3 = G2->deckCount[0];
	d4 = G1->deckCount[1];
	
	printf("\n*********************\n");
	printf("Testing shuffle() method\n");
	printf("*********************\n\n");	
	
	if((d1 == d2) && (d2 == d3) && (d3 == d4)){
		printf("All decks have the same amount of cards. \n");
	} else {
		printf("Warning, all decks do not have the same amount of cards. \n");
		printf("Game 1, Player 1 Deck Count: %i.\n",d1);
		printf("Game 1, Player 2 Deck Count: %i.\n",d2);
		printf("Game 2, Player 1 Deck Count: %i.\n",d3);
		printf("Game 2, Player 2 Deck Count: %i.\n",d4);		
	}
	
	//Make sure the discard pile is 0
	if(G1->discardCount[0] == 0){
		printf("Test Passed: Game 1, Player 1 discard pile is 0. \n");
	} else {
		printf("Test Failed: Game 1, Player 1 discard pile is not 0; it is %i. \n", G1->discardCount[0]);
	}
	if(G1->discardCount[1] == 0){
		printf("Test Passed: Game 1, Player 2 discard pile is 0. \n");
	} else {
		printf("Test Failed: Game 1, Player 1 discard pile is not 0; it is %i. \n", G1->discardCount[1]);
	}
	if(G2->discardCount[0] == 0){
		printf("Test Passed: Game 2, Player 1 discard pile is 0. \n");
	} else {
		printf("Test Failed: Game 1, Player 1 discard pile is not 0; it is %i. \n", G2->discardCount[0]);
	}
	if(G2->discardCount[1] == 0){
		printf("Test Passed: Game 2, Player 2 discard pile is 0. \n");
	} else {
		printf("Test Failed: Game 1, Player 1 discard pile is not 0; it is %i. \n", G2->discardCount[1]);
	}
		
	//Test a shuffle for Game 1, Player 1
	res1 = shuffle(0, G1);
	if(res1 >= 0){
		printf("Shuffle for Game 1, Player 1 successful. \n");
	} else {
		printf("Error shuffling Game 1, Player 1. \n");
	}
	//Test a shuffle for Game 2, Player 1
	res2 = shuffle(0, G2);
	if(res2 >= 0){
		printf("Shuffle for Game 2, Player 1 successful. \n");
	} else {
		printf("Error shuffling Game 2, Player 1. \n");
	}	
	
	//Make sure the two decks are different after shuffling both
	if(memcmp(G1->deck[0], G2->deck[0], sizeof(G1->deck[0])) != 0){
		printf("Test Passed: The two decks were different after calls to shuffle. \n");
	} else {
		printf("Test Passed: The two decks were the same after shuffling. \n");
	}

	//Check to see what would happen if we shuffle an empty deck
	G1->deckCount[0] = 0;
	
	res1 = shuffle(0, G1);
	if(res1 >= 0){
		printf("Test Failed: shuffle() shuffled an empty deck. \n");
	} else {
		printf("Test Passed: shuffle() observed that the deck was empty. \n");
	}

	printf("\n");	
	return;
}