/* ---------------------------------------------------------------------------------
 * File: unittest2.c
 * Unit test for testing the buyCard() function in dominion.c
 * unittest1: unittest1.c dominion.o rngs.o
 * 		gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 *
 * ---------------------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

//set NOISY_TEST to 0 to remove printfs from output
#define NOISY_Test 1
#define DEBUG 0

int main() {
	int errors = 0;
	int seed = 2000;
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int i, j, k, player, supplyPos;
	struct gameState gState;

	printf("Testing buyCard()\n");

	SelectStream(2); //rngs.h
	PutSeed(3);  //rngs.h

	for (i = 0; i < 2000; i++){
		for(j = 0; j < sizeof(struct gameState); j++){
			((char*)&gState)[j] = 500; //floor(Random() * 256);
		}
		player = (int)(Random() * MAX_PLAYERS); //rngs.h and dominion.h, respectively
		gState.deckCount[player] = 50; //floor(Random() * MAX_DECK);
		gState.handCount[player] = 100; //floor(Random() * MAX_HAND);
		gState.discardCount[player] = 50; //floor(Random() * MAX_DECK);
		gState.numBuys = 1;

		for (k = 0; k < gState.handCount[player]; k++){
			gState.hand[player][i] = (int)(Random() * MAX_HAND);
		}
		for (k = 0; k < gState.discardCount[player]; k++){
			gState.discard[player][i] = (int)(Random() * MAX_DECK);
		}
		for (k = 0; k < gState.deckCount[player]; k++){
			gState.deck[player][i] = (int)(Random() * MAX_DECK);
		}
		/*for (i = 0; i <= treasure_map; i++){
			state->supplyCount[i] = (int)(Random() * 46); // 46 is the max # of copper treasure cards
		}*/
		supplyPos = 500(int)(Random() * (treasure_map + 1));
		errors += testBuyCard(supplyPos, &gState);
	}
	if (errors == 0){
		printf("All Tests Passed\n");
	}
	else{
		printf("Tests Failed\n");
	}
	return 0;
}

int testBuyCard(int supplyPos, struct gameState *gS){
	int r1 = 0;
	int r2 = 0;
	int errors = 0;
	struct gameState gS1;

	memcpy(&gS1, gS, sizeof(struct gameState));

	//r1 = gS1->supplyCount[card];

	//r2 = supplyCount(card, gS);

	if (gS1.numBuys < 1) {
		printf("No buys remaining\n");
		r1 = -1;
	}
	else if (supplyCount(supplyPos, &gS1) < 1){
		printf("That type of card is expended\n");
		r1 = -1;
	}
	else if (gS1.coins < getCost(supplyPos)){
		printf("Insufficient funds for that purchase\n");
		r1 = -1;
	}
	else {
		gS1.phase = 1;
		gainCard(supplyPos, &gS1, 0, gS1.whoseTurn);
		gS1.coins = ((gS1.coins) - (getCost(supplyPos)));
		gS1.numBuys--;
		r1 = 0;
	} 	
	
	r2 = buyCard(supplyPos, gS);
	if (r1 != r2){
		printf("Failed Test.  Expected: %d Computed: %d\n", r1, r2);
		errors++;
	}
	
	if (memcpy(&gS1, gS, sizeof(struct gameState))){
		printf("Failed Test.  Game states are not identical\n");
		errors++;
	}
	return errors;	

}
