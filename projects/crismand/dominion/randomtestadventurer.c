/*
************************************
This is a random tester for the method pAdventurer() from dominion.c  
pAdventurer stands for Play Adventurer

It initializes a gameState, randomizes a bunch of things in the state (but not anything that completely breaks
the code.  Then it calls pAdventurer, then checks the results.  

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
#include <time.h>

float T1 = 0;
float T2 = 0;
float T3 = 0;
float T4 = 0;
float T5 = 0;
float T6 = 0;
float T7 = 0;
float T8 = 0;

void printR(int tests);
void checkGS(struct gameState *G1, struct gameState *G2, int test);

int main(int argc, char *argv[]) {

    srand(time(NULL));
	
	int i, j, res;
	int tests = 1000;
	
	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};



	for(i = 1; i <= tests; ++i){
		
		initializeGame(2, k, 2, G1);	
		
		//Randomize a bunch of the game state variables
		G1->phase = rand() % 20;
		G1->numActions = rand() % 20;
		G1->coins = rand() % 50;				
		G1->numBuys = rand() % 50;
		G1->handCount[0] = rand() % 20 + 5;
		
		//Randomize any additional cards that were added to the hand, deck, and discard.
		for(j = 5; j < G1->handCount[0]; ++j){
				
			G1->hand[0][j] = rand() % 27;
		}
		G1->deckCount[0] = rand() % 100 + 10;
		for(j = 10; j < G1->deckCount[0]; ++j){
				
			G1->deck[0][j] = rand() % 27;
		}
		G1->discardCount[0] = rand() % 100;
		for(j = 0; j < G1->discardCount[0]; ++j){
				
			G1->discard[0][j] = rand() % 27;
		}		
		
		//Make sure the feast card is in the hand.
		G1->hand[0][G1->handCount[0]] = adventurer;
		G1->handCount[0]++;
		//Copy the state before calling the card.
		memcpy(G2, G1, sizeof(struct gameState));
		res = pAdventurer(G1, (G1->handCount[0] - 1));
		
		checkGS(G1, G2, i);
		
	}
	
	printR(tests);
	
    return 0;
}

void checkGS(struct gameState *G1, struct gameState *G2, int test){
	
		
	printf("\n*********************\n");
	printf("Testing Adventurer card effect\n");
	printf("Test %i.\n", test);
	printf("*********************\n\n");	
	
	
	//Test to see if 2 cards were added to the hand (but the adventurer card should've been discarded.  Net +1)
	if(G1->handCount[0] == (G2->handCount[0] + 1)){
		printf("Test 1 Passed, Hand Count. Expected: %i Got: %i. \n", (G2->handCount[0] + 1), G1->handCount[0]);
		T1 = T1 + 1;
	} else {
		printf("Test 1 Failed, Hand Count. Expected: %i Got: %i. \n", (G2->handCount[0] + 1), G1->handCount[0]);
	}
	
	//Test to see if both cards that were added to the hand are treasure cards
	if(G1->hand[0][G1->handCount[0] - 2] == copper || G1->hand[0][G1->handCount[0] - 2] == silver || G1->hand[0][G1->handCount[0] - 2] == gold){
		printf("Test 2 Passed, first card added was a treasure card. \n");
		T2 = T2 + 1;
	} else {
		printf("Test 2 Failed, first card added was not a treasure card. \n");
	}
	
	if(G1->hand[0][G1->handCount[0] - 1] == copper || G1->hand[0][G1->handCount[0] - 1] == silver || G1->hand[0][G1->handCount[0] - 1] == gold){
		printf("Test 3 Passed, second card added was a treasure card. \n");
		T3 = T3 + 1;
	} else {
		printf("Test 3 Failed, second card added was not a treasure card. \n");
	}
	
	//Test to see if other cards were discarded.	
	if(G1->discardCount[0] > G2->discardCount[0]){
		printf("Test 4 Passed, Discard Count. Expected: > %i Got: %i. \n", (G2->discardCount[0]), G1->discardCount[0]);
		T4 = T4 + 1;
	} else {
		printf("Test 4 Failed, Discard Count. Expected: > %i Got: %i. \n", (G2->discardCount[0]), G1->discardCount[0]);
	}
	
	//Test to see if number of actions was decreased by 1;
	if(G1->numActions == (G2->numActions - 1)){
		printf("Test 5 Passed, Actions. Expected: %i Got: %i. \n", (G2->numActions - 1), G1->numActions);
		T5 = T5 + 1;
	} else {
		printf("Test 5 Failed, Actions. Expected: %i Got: %i. \n", (G2->numActions - 1), G1->numActions);
	}	
	
	//Test to see if number of coins was altered (shouldn't be)
	if(G1->coins == G2->coins){
		printf("Test 6 Passed, Coins. Expected: %i Got: %i. \n", (G2->coins), G1->coins);
		T6 = T6 + 1;
	} else {
		printf("Test 6 Failed, Coins. Expected: %i Got: %i. \n", (G2->coins), G1->coins);
	}

	//Test to see if number of buys was altered (shouldn't be)
	if(G1->numBuys == G2->numBuys){
		printf("Test 7 Passed, Buys. Expected: %i Got: %i. \n", (G2->numBuys), G1->numBuys);
		T7 = T7 + 1;
	} else {
		printf("Test 7 Failed, Buys. Expected: %i Got: %i. \n", (G2->numBuys), G1->numBuys);
	}
	
	//Test to see if the deck still had the same total number of cards as the Game 2 Player 1 deck.
	if(G1->deckCount[0] == G2->deckCount[0]){
		printf("Test 8 Passed, Deck Count. Expected: %i Got: %i. \n", (G2->deckCount[0]), G1->deckCount[0]);
		T8 = T8 + 1;
	} else {
		printf("Test 8 Failed, Deck Count. Expected: %i Got: %i. \n", (G2->deckCount[0]), G1->deckCount[0]);
	}
	printf("\n");	
	return;
}

void printR(int tests){
	
	int p1 = (int)((T1/tests) * 100);
	int p2 = (int)((T2/tests) * 100);
	int p3 = (int)((T3/tests) * 100);
	int p4 = (int)((T4/tests) * 100);	
	int p5 = (int)((T5/tests) * 100);
	int p6 = (int)((T6/tests) * 100);	
	int p7 = (int)((T7/tests) * 100);
	int p8 = (int)((T8/tests) * 100);
	
	printf("\n*********************\n");
	printf("Results of Testing\n");
	printf("*********************\n\n");	
	
	printf("Test 1 PASSED %i out of %i.  %i%%.\n", (int)(T1), tests, p1);
	printf("Test 2 PASSED %i out of %i.  %i%%.\n", (int)(T2), tests, p2);		
	printf("Test 3 PASSED %i out of %i.  %i%%.\n", (int)(T3), tests, p3);
	printf("Test 4 PASSED %i out of %i.  %i%%.\n", (int)(T4), tests, p4);
	printf("Test 5 PASSED %i out of %i.  %i%%.\n", (int)(T5), tests, p5);
	printf("Test 6 PASSED %i out of %i.  %i%%.\n", (int)(T6), tests, p6);
	printf("Test 7 PASSED %i out of %i.  %i%%.\n", (int)(T7), tests, p7);
	printf("Test 8 PASSED %i out of %i.  %i%%.\n", (int)(T8), tests, p8);
	printf("\n ****************************\n\n COVERAGE DATA \n\n");
	
}