/* ---------------------------------------------------------------------------------
 * File: cardtest3.c
 * Unit test for testing the Great Hall card in dominion.c
 * cardtest3: cardtest3.c dominion.o rngs.o
 * 		gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	int i, j, player, card, handPos;
	int pick1, pick2, pick3;
	struct gameState gState;

	printf("Testing great_hall\n");

	SelectStream(2); //rngs.h
	PutSeed(2);  //rngs.h

	for (i = 0; i < seed; i++){
		for(j = 0; j < sizeof(struct gameState); j++){
			((char*)&gState)[j] = floor(Random() * 512);
		}
		player = (int)(Random() * MAX_PLAYERS); //rngs.h and dominion.h, respectively
		gState.deckCount[player] = floor(Random() * MAX_DECK);
		gState.handCount[player] = floor(Random() * MAX_HAND);
		gState.discardCount[player] = floor(Random() * MAX_DECK);
		gState.whoseTurn = player;
		gState.playedCardCount = 0;

		gState.outpostPlayed = 0;
		gState.phase = 0;
		gState.numActions = 1;
		gState.numBuys = 1;
		gState.playedCardCount = 0;

		for (i = 0; i < gState.handCount[player]; i++){
			if (Random() > 1){
				gState.hand[player][i] = copper + (int)(Random() * (gold - copper + 1));
			}
			else{
				gState.hand[player][i] 	= (int)(Random() * MAX_HAND);
			}
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
		card = great_hall;
		pick1 = (int)(Random() * (treasure_map +1));
		pick2 = (int)(Random() * (treasure_map +1));
		pick3 = (int)(Random() * (treasure_map +1));
		handPos = (int)(Random() * gState.handCount[player]);
		errors += testGreatHall(player, card, pick1, pick2, pick3, &gState, handPos);
	}
	if (errors == 0){
		printf("All Tests Passed\n");
	}
	else{
		printf("Tests Failed\n");
	}
	return 0;
}

int testGreatHall(int player, int card, int pick1, int pick2, int pick3, struct gameState *gS, int handPos){
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
		printf("Failed Test.  Game states are not identical\n");
		errors++;
	}
	if (gS1.handCount[player] != gS->handCount[player]){
		printf("Failed Test.  Game states are not identical\n");
		errors++;
	}
	return errors;	

}
