/* ---------------------------------------------------------------------------------
 * File: cardtest4.c
 * Unit test for testing the Feast card in dominion.c
 * cardtest4: cardtest4.c dominion.o rngs.o
 * 		gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	int i, j, k, player, card, handPos;
	int pick1, pick2, pick3;
	struct gameState gState;

	printf("Testing feast\n");

	SelectStream(2); //rngs.h
	PutSeed(3);  //rngs.h

	for (k = 0; k < 1000; k++){
		for(j = 0; j < (.1 * sizeof(struct gameState)); j++){
			((char*)&gState)[j] = floor(Random() * 256);
		}
		player = (int)(Random() * MAX_PLAYERS); //rngs.h and dominion.h, respectively
		gState.deckCount[player] = floor(Random() * MAX_DECK);
		gState.handCount[player] = floor(Random() * MAX_HAND);
		gState.discardCount[player] = floor(Random() * MAX_DECK);
		gState.whoseTurn = player;

		for (i = 0; i < gState.handCount[player]; i++){
			gState.hand[player][i] 	= (int)(Random() * MAX_HAND);
		}
		for (i = 0; i < gState.discardCount[player]; i++){
			gState.discard[player][i] = (int)(Random() * MAX_DECK);
		}
		for (i = 0; i < gState.deckCount[player]; i++){
			gState.deck[player][i] = (int)(Random() * MAX_DECK);
		}
		for (i = 0; i <= treasure_map; i++){
			gState.supplyCount[i] = (int)(Random() * 46); // 46 is the max # of copper treasure cards
		}
		card = feast;
		pick1 =1;
		pick2 = 2;
		pick3 = 3;
		handPos = (int)(Random() * gState.handCount[player]);
		errors += testFeast(player, card, pick1, pick2, pick3, &gState, handPos);
	}
	if (errors == 0){
		printf("All Tests Passed\n");
	}
	else{
		printf("Tests Failed\n");
	}
	return 0;
}

int testFeast(int player, int card, int pick1, int pick2, int pick3, struct gameState *gS, int handPos){
	int r1 = 0;
	int r2 = 0;
	int errors = 0;
	struct gameState gS1;

	memcpy(&gS1, gS, sizeof(struct gameState));

	drawCard(player, &gS1);
	gS1.numActions++;
	discardCard(handPos, player, &gS1, 0);

	r2 = cardEffect(card, pick1, pick2, pick3, gS, handPos, 0);

	if (r1 != r2){
		printf("Failed Test.  Expected: %d Computed: %d\n", r1, r2);
		errors++;
	}
	
	if (gS1.numActions != gS->numActions){
		printf("Failed Test.  Game states are not identical\n");
		errors++;
	}
	if (gS1.playedCardCount != gS->playedCardCount){
		printf("Failed Test.  Game states are not identical");
		errors++;
	}
	if (gS1.handCount[player] != gS->handCount[player]){
		printf("Failed Test.  Game states are not identical\n");
		errors++;
	}
	return errors;	

}
