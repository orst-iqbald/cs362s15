/* -----------------------------------------------------------------------
 * test for play card adventurer in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest2:cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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

int numTreasures(struct gameState *state, int player){
	int treasure = 0;
	int i, card;
	
	for (i=0; i < state->handCount[player]; i++) {
		card = state->hand[player][i];
		if (card == copper || card == gold || card == silver)
			treasure++;
	}
	
	return treasure;
}

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
    int i;
	
	// comp value holders
	int init_numTreas=0, act_numTreas=0, deltaT =0;
	int init_discard=0, act_discard=0, deltaD=0;

	// set to init false - meaning not okay
	int bool_Treas[] = { 0, 0, 0};
	int bool_Discard[] = {0,0,0};
	
	    
    printf ("TESTING adventurer card play\n");
	G = newGame();  // found game constructor in code
	   
    for (i=0; i < 3; i++) {
    	memset(G, 0, sizeof(struct gameState));  //zero out
    	initG(G, i); //   
    	init_numTreas = numTreasures(G, 0);
    	init_discard = G->discardCount[0];
    	pcdAdventurer(G, 0);
    	act_numTreas = numTreasures(G,0);
    	act_discard = G->discardCount[0];
    	deltaT = act_numTreas - init_numTreas;
    	deltaD = act_discard - init_discard;

		if (i == 0) {
			if (deltaT == 2) bool_Treas[i] = 1;
			if (deltaD == 1) bool_Discard[i] = 1;
#if (NOISY_TEST == 1)		
			printf("Test%d delta treas act:%d expected:%d\n", i, deltaT, 2);
			printf("Test%d delta discard act:%d expected:%d\n", i, deltaD, 1);
#endif
		} else if (i==1) {
			if (deltaT == 2) bool_Treas[i] = 1;
			if (deltaD == 5-3) bool_Discard[i] = 1;
#if (NOISY_TEST == 1)
			printf("Test%d delta treas act:%d expected:%d\n", i, deltaT, 2);
			printf("Test%d delta discard act:%d expected:%d\n", i, deltaD, 5-3);
#endif
		} else {
			if (deltaT == 1) bool_Treas[i] = 1;
			if (deltaD == 8-3) bool_Discard[i] = 1;
#if (NOISY_TEST == 1)
			printf("Test%d delta treas act:%d expected:%d\n", i, deltaT, 1);
			printf("Test%d delta discard act:%d expected:%d\n", i, deltaD, 8-3);
#endif
		}
	}
	
	// output results
	for (i=0; i < 3; i++) {
		printf("\n");
		if (bool_Treas[i]) printf("Test%d: adventurer card play numTreas: PASS\n", i);
		else  printf("Test%d: adventurer card play numTreas: FAIL\n", i); 
		if (bool_Discard[i]) printf("Test%d: adventurer card play numDiscard: PASS\n", i);
		else  printf("Test%d: adventurer card play numDiscard: FAIL\n", i);		
	}
	
	return 0;
}
