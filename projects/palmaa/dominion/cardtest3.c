/* -----------------------------------------------------------------------
 * test for play card village in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest3:cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

void initG(struct gameState *state, int tcase) {
		
	state->numPlayers = 1;
	
	state->hand[0][0] = adventurer;
	state->hand[0][1] = copper;
	state->hand[0][2] = gold;
	state->hand[0][3] = smithy;
	state->hand[0][4] = village;
	state->handCount[0] = 5;
	
	state->deck[0][0] = sea_hag;
	state->deck[0][1] =silver;
	state->deck[0][2] = gardens;
	if (tcase == 0) {
		state->deck[0][3] = copper;
		state->deck[0][4] = curse;
		state->deck[0][5] = gold;
	} else {
		state->deck[0][3] = mine;
		state->deck[0][4] = curse;
		state->deck[0][5] = cutpurse;
	}
	state->deckCount[0] = 6;
	
	if (tcase == 1) {
		state->discard[0][0] = copper;
		state->discard[0][1] = silver;
		state->discard[0][2] = gold;
	} else {
		state->discard[0][0] = steward;
		state->discard[0][1] = tribute;
		state->discard[0][2] = embargo;
	}
	state->discardCount[0] = 3;
}
	

int main() {
    
    struct gameState *G;
	
	// comp value holders
	int init_numActs=0, act_numActs=0, deltaA =0;
	int init_numCard=0, act_numCard=0, deltaC=0;
	int init_discard=0, act_discard=0, deltaD=0;

	// set to init false - meaning not okay
	int bool_Acts = 0;
	int bool_Discards = 0;
	int bool_Cards = 0;
	
	    
    printf ("TESTING village card play\n");
	G = newGame();  // found game constructor in code
	memset(G, 0, sizeof(struct gameState));  //zero out   
   
    initG(G, 0); //   
    init_numActs = G->numActions;
    init_discard = G->discardCount[0];
    init_numCard = G->handCount[0];
    
    cardEffect(village, 1, 1, 1, G, 4, NULL);
    
    act_numActs = G->numActions;
    act_discard = G->discardCount[0];
    act_numCard = G->handCount[0];
    deltaA = act_numActs - init_numActs;
    deltaD = act_discard - init_discard;
    deltaC = act_numCard - init_numCard;

	if (deltaA == 2) bool_Acts = 1;
	if (deltaD == 1) bool_Discards = 1;
	if (deltaC== 0) bool_Cards = 1;
#if (NOISY_TEST == 1)		
	printf("Delta Actions act:%d expected:%d\n", deltaA, 2);
	printf("Delta Discard act:%d expected:%d\n", deltaD, 1);
	printf("Delta Cards act:%d expected:%d\n", deltaC, 0);
#endif
	
	// output results

	printf("\n");
	if (bool_Acts) printf("Village card play numActions: PASS\n");
	else  printf("Village card play numActions: FAIL\n"); 
	if (bool_Discards) printf("Village card play numDiscard: PASS\n");
	else  printf("Village card play numDiscard: FAIL\n");		
	if (bool_Cards) printf("Village card play numCards: PASS\n");
	else  printf("Village card play numCards: FAIL\n");
	
	return 0;
}
