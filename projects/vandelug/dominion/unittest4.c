/* ---------------------------------------------------------------------------------
 * File: unittest4.c
 * Unit test for testing the scoreFor() function in dominion.c
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

    printf("Testing scoreFor()\n");

    SelectStream(2); //rngs.h
    PutSeed(2);  //rngs.h

    for (i = 0; i < 1000; i++){
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

	errors += testScoreFor(player, &gState);
    }
    if (errors == 0){
	printf("All Tests Passed\n");
    }
    else{
	printf("Tests Failed\n");
    }
    return 0;
}

int testScoreFor(int player, struct gameState *gS){
    int s1 = 0;
    int s2 = 0;
    int errors = 0;
    struct gameState gS1;
    int i;

    memcpy(&gS1, gS, sizeof(struct gameState));

    //r1 = gS1->supplyCount[card];

    //r2 = supplyCount(card, gS);

    for (i = 0; i < gS1.handCount[player]; i++){
	if (gS1.hand[player][i] == estate){
	    s1 = s1 + 1;
	}
	if (gS1.hand[player][i] == duchy){
	    s1 = s1 + 3;
	}
	if (gS1.hand[player][i] == province){
	    s1 = s1 - 6;
	}
	if (gS1.hand[player][i] == great_hall){
	    s1 = s1 + 1;
	}
	if (gS1.hand[player][i] == gardens){
	    s1 = s1 + (fullDeckCount(player, 0, &gS1) / 10);
	}
	if (gS1.hand[player][i] == curse){
	    s1 = s1 - 1;
	}
    }

    for (i = 0; i < gS1.discardCount[player]; i++){
	if (gS1.discard[player][i] == estate){
	    s1 = s1 + 1;
	}
	if (gS1.discard[player][i] == duchy){
	    s1 = s1 + 3;
	}
	if (gS1.discard[player][i] == province){
	    s1 = s1 - 6;
	}
	if (gS1.discard[player][i] == great_hall){
	    s1 = s1 + 1;
	}
	if (gS1.discard[player][i] == gardens){
	    s1 = s1 + (fullDeckCount(player, 0, &gS1) / 10);
	}
	if (gS1.discard[player][i] == curse){
	    s1 = s1 - 1;
	}
    }

    for (i = 0; i < gS1.deckCount[player]; i++){
	if (gS1.deck[player][i] == estate){
	    s1 = s1 + 1;
	}
	if (gS1.deck[player][i] == duchy){
	    s1 = s1 + 3;
	}
	if (gS1.deck[player][i] == province){
	    s1 = s1 - 6;
	}
	if (gS1.deck[player][i] == great_hall){
	    s1 = s1 + 1;
	}
	if (gS1.deck[player][i] == gardens){
	    s1 = s1 + (fullDeckCount(player, 0, &gS1) / 10);
	}
	if (gS1.deck[player][i] == curse){
	    s1 = s1 - 1;
	}
    }

    s2 = scoreFor(player, gS);
    if (s1 != s2){
	printf("Failed Test.  Expected: %d Computed: %d\n", s2, s1);
	errors++;
    }

    if (memcmp(&gS1, gS, sizeof(struct gameState))){
	printf("Failed Test.  Game states are not identical\n");
	errors++;
    }
    return errors;	

}
