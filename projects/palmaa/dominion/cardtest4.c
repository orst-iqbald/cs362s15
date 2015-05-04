/* -----------------------------------------------------------------------
 * test for play card great hall in dominion.c
 * Include the following lines in your makefile:
 *
 * cardtest4:cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	state->hand[0][3] = great_hall;
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
	
	    
    printf ("TESTING great_hall card play\n");
	G = newGame();  // found game constructor in code
	memset(G, 0, sizeof(struct gameState));  //zero out   
   
    initG(G, 0); //   
    init_numActs = G->numActions;
    init_discard = G->discardCount[0];
    init_numCard = G->handCount[0];
    
    cardEffect(great_hall, 1, 1, 1, G, 3, NULL);
    
    act_numActs = G->numActions;
    act_discard = G->discardCount[0];
    act_numCard = G->handCount[0];
    deltaA = act_numActs - init_numActs;
    deltaD = act_discard - init_discard;
    deltaC = act_numCard - init_numCard;

	if (deltaA == 1) bool_Acts = 1;
	if (deltaD == 1) bool_Discards = 1;
	if (deltaC== 0) bool_Cards = 1;
#if (NOISY_TEST == 1)		
	printf("Delta Actions act:%d expected:%d\n", deltaA, 1);
	printf("Delta Discard act:%d expected:%d\n", deltaD, 1);
	printf("Delta Cards act:%d expected:%d\n", deltaC, 0);
#endif
	
	// output results

	printf("\n");
	if (bool_Acts) printf("Great_Hall card play numActions: PASS\n");
	else  printf("Great_Hall card play numActions: FAIL\n"); 
	if (bool_Discards) printf("Village card play numDiscard: PASS\n");
	else  printf("Great_Hall card play numDiscard: FAIL\n");		
	if (bool_Cards) printf("Great_Hall card play numCards: PASS\n");
	else  printf("Great_Hall card play numCards: FAIL\n");
	
	return 0;
}
