/* ---------------------------------------------------------------------------------
 * File: unittest3.c
 * Unit test for testing the isGameOver() function in dominion.c
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

int main() {
	int errors = 0;
	int seed = 2000;
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int i, j, k, player, card;
	struct gameState gState;

	printf("Testing isGameOver()\n");

	SelectStream(2); //rngs.h
	PutSeed(2);  //rngs.h

	for (i = 0; i < seed; i++){
		for(j = 0; j < (.1 * sizeof(struct gameState)); j++){
			((char*)&gState)[j] = floor(Random() * 512);
		}
		player = (int)(Random() * MAX_PLAYERS); //rngs.h and dominion.h, respectively
		gState.deckCount[player] = floor(Random() * MAX_DECK);
		gState.handCount[player] = floor(Random() * MAX_HAND);
		gState.discardCount[player] = floor(Random() * MAX_DECK);

		for (k = 0; k < gState.handCount[player]; k++){
			gState.hand[player][i] = (int)(Random() * MAX_HAND);
		}
		for (k = 0; k < gState.discardCount[player]; k++){
			gState.discard[player][i] = (int)(Random() * MAX_DECK);
		}
		for (k = 0; k < gState.deckCount[player]; k++){
			gState.deck[player][i] = (int)(Random() * MAX_DECK);
		}
		for (k = 0; k <= treasure_map; k++){
			gState.supplyCount[i] = (int)(Random() * 46); // 46 is the max # of copper treasure cards
		}
		//card = (int)(Rand() * (treasure_map +1));
		errors += testIsGameOver(&gState);
	}
	if (errors == 0){
		printf("All Tests Passed\n");
	}
	else{
		printf("Tests Failed\n");
	}
	return 0;
}

int testIsGameOver(struct gameState *gS){
	int r1 = 0;
	int r2 = 0;
	int errors = 0;
	struct gameState gS1;
	int i, j = 0;

	memcpy(&gS1, gS, sizeof(struct gameState));

	//r1 = gS1->supplyCount[card];

	//r2 = supplyCount(card, gS);

	if (gS1.supplyCount[province] == 0){
		r1 = 1;
	}

	for (i = 0; i <= treasure_map; i++){
		if (gS1.supplyCount[i] == 0){
			j++;
		}
	}
	if(j >= 3){
		r1 = 1;
	}

	r2 = isGameOver(gS);	

	if (r1 != r2){
		printf("Failed Test.  Expected: %d Computed: %d\n", r1, r2);
		errors++;
	}
	
	if (memcmp(&gS1, gS, sizeof(struct gameState))){
		printf("Failed Test.  Game states are not identical\n");
		errors++;
	}
	return errors;	

}
