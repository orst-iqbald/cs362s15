/*
************************************
This is a unit test for the method buyCard() from dominion.c  

************************************
*/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void testBuy(struct gameState *G1, struct gameState *G2);

int main(int argc, char *argv[]) {

	struct gameState *G1 = malloc(sizeof(struct gameState));
	struct gameState *G2 = malloc(sizeof(struct gameState));

	int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 2, G1);	
	initializeGame(2, k, 2, G2);

    testBuy(G1, G2);
	
    return 0;
}

void testBuy(struct gameState *G1, struct gameState *G2){
	
	int i;
	int j = 0;
	
	//Set the game states to be able to test various scenarios
	G1->numBuys = 11;
	G1->coins = 50;
	G2->numBuys = 1;
	G2->coins = 5;
		
	printf("\n*********************\n");
	printf("Testing buyCard() method\n");
	printf("*********************\n\n");	
	
	//Test buying all the cards in a pile + 1
	for(i = 0; i < 11; ++i){
		
		if(buyCard(smithy, G1) == 0){
			j++;
			printf("Buy 1 smithy successful, now have %i. \n",j);
		} else {
			printf("Buy failed. \n");
		}
	}
	//Check expected results of game state
	if(G1->numBuys > 1){
		printf("Test Failed, number of buys not adequately reduced in previous tests.\n");
	} else {
		printf("Test Passed, buy should be 1 or fewer.\n");
	}
	if(G1->coins > 10){
		printf("Test Failed, number of coins not adequately reduced in previous tests. Actual Coins: %i.\n", G1->coins);
	} else {
		printf("Test Passed, coins should be 10 or fewer. \n");
	}

	//Test buying some cards we can't afford
	if(buyCard(province, G2) == 0){
		printf("Test Failed, allowed to buy province despite not having the money.\n");
	} else {
		printf("Test Passed, didn't have the money for a province.\n");
	}
	if(buyCard(adventurer, G2) == 0){
		printf("Test Failed, allowed to buy adventurer despite not having the money.\n");
	} else {
		printf("Test Passed, didn't have the money for an adventurer card.\n");
	}	
	
	//Buy a card we can afford
	if(buyCard(mine, G2) == 0){
		printf("Test Passed, allowed to buy mine.\n");
	} else {
		printf("Test Failed, couldn't buy mine.\n");
	}		
	
	//Reset buys but not money:
	G2->numBuys = 1;
	G2->coins = 2;	
	//Test buying a card we can't afford
	if(buyCard(mine, G2) == -1){
		printf("Test Passed, didn't allow me to buy mine when I couldn't afford it.\n");
	} else {
		printf("Test Failed, allowed to buy mine despite not having the money.\n");
	}	

	//Reset coins but not buys:
	G2->numBuys = 0;
	G2->coins = 2;	
	//Test buying a card that isn't in the deck
	if(buyCard(curse, G2) == -1){
		printf("Test Passed, didn't allow me to buy curse when I had no buys.\n");
	} else {
		printf("Test Failed, allowed to buy curse when I had no buys.\n");
	}		
	
	G2->numBuys = 1;
	G2->coins = 5;	
	//Test buying a card that isn't in the deck
	if(buyCard(feast, G2) == 0){
		printf("Test Failed, allowed to buy feast despite it not being in the set of kingdom cards.\n");
	} else {
		printf("Test Passed, didn't allow me to buy feast.\n");
	}
	printf("\n");		
	return;
}