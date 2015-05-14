//tests Smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main() {
	int errors = 0;
	int seed = 2000;
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int i, j, player, card, handPos;
	int pick1, pick2, pick3;
	struct gameState gState;

	printf("Testing Smithy\n");

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
		card = smithy;
		pick1 = (int)(Random() * (treasure_map +1));
		pick2 = (int)(Random() * (treasure_map +1));
		pick3 = (int)(Random() * (treasure_map +1));
		handPos = (int)(Random() * gState.handCount[player]);
		errors += testSmithy(player, card, pick1, pick2, pick3, &gState, handPos);
	}
	if (errors == 0){
		printf("All Tests Passed");
	}
	else{
		printf("Tests Failed");
	}
	return 0;
}

int testSmithy(int player, int card, int pick1, int pick2, int pick3, struct gameState *gS, int handPos){
	int r11, r1 = 0;
	int r22, r2 = 0;
	int errors = 0;
	int i = 0;
	struct gameState gS1;

	memcpy(&gS1, gS, sizeof(struct gameState));

	while(i < 3){
		drawCard(player, &gS1);
		i++;
	}
	discardCard(handPos, player, &gS1, 0);

	r2 = cardEffect(card, pick1, pick2, pick3, gS, handPos, 0);
	playSmithy(handPos, player, gS);
	

	if (r1 != r2){
		printf("Failed Test.  Expected: %d Computed: %d", r1, r2);
		errors++;
	}
	if (gS1.playedCardCount != gS->playedCardCount){
		printf("Failed Test.  Game states are not identical");
		errors++;
	}
	if (gS1.handCount[player] != gS->handCount[player]){
		printf("Failed Test.  Game states are not identical");
		errors++;
	}
	return errors;	

}



