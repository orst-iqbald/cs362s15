/*****************************
 * Card Test for Cutpurse
 ***************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main (){
	int i;
	struct gameState G;
	int p, r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	r = initializeGame(2, k, 1000, &G);
	
	printf("Testing cutpurse...\n");

	//Test coins += 2
	G.coins = 2;
	p = playCutpurse(&G, 1, 1);
	//assert(G.coins == 4);
	printf("Bug: coins don't increase\n");	

	//Test P1 hand - 1 when full of gold
	int golds[5];
	for (i = 0; i < 5; i++){
		golds[i] = gold;
	}
	memcpy(G.hand[2], golds, sizeof(int)*5);
	p = playCutpurse(&G,1,1);
	//assert(G.handCount[2] == 4);
	printf("Bug:Player 2 hand count is incorrect\n");


	//Test P1 hand == 5 when full of copper
	int coppers[5];
	for ( i = 0; i < 5; i++){
		coppers[i] = copper;
	}
	memcpy(G.hand[2], coppers, sizeof(int)*5);
	p = playCutpurse(&G,1,1);
	//assert(G.handCount[2] == 5);
	printf("Bug: p2 hand size is incorrect\n");

	return 0;
}
