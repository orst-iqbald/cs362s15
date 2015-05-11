/* -----------------------------------------------------------------------
 * random test for play card adventurer in dominion.c
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
#include <math.h>  //for rand()


#define PLAYERS 3
#define NUMTESTS 5000

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int numTreasures(struct gameState *state, int player, char* what){
	int treasure = 0;
	int i, card;
	int limit;
	int* holder;
	
	if (strcmp(what, "hand") == 0) {
	  limit = state->handCount[player];
	  holder = state->hand[player];
	} else if (strcmp(what, "deck") == 0) {
	  limit = state->deckCount[player];
	  holder = state->deck[player];
	} else {
	  limit = state->discardCount[player];
	  holder = state->discard[player];
	}
	
	for (i=0; i < state->handCount[player]; i++) {
		card = holder[i];
		if (card == copper || card == gold || card == silver)
			treasure++;
	}
	
	return treasure;
}


int main() {
    
    struct gameState *G;
    int i, r;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, \
     remodel, smithy, village, baron, great_hall};
	
	// comp value holders
	int init_numTreas, act_numTreas, deltaT , expect_dT;
	int init_discard, act_discard, deltaD, expect_dD;
	int init_deck, act_deck, deltaDK;

	// keep track of number pass/fails
	int pass_Treas=0, fail_Treas=0;
	int pass_Discard=0, fail_Discard=0;
	
	int decTreas, discTreas;
	int testrun = 0;
	    
    printf ("RANDOM ? TESTING adventurer card play\n");
    
    G = newGame();
    
    for (i=0; i < NUMTESTS; i++) {
      //initialize game
      r = initializeGame(PLAYERS, kingdomCards, rand(), G);
      if (r==0) { //only proceed if initialization okay
        testrun++; //increment test run
        
        
        //get initial state 
        int my_player = G->whoseTurn;
        init_numTreas = numTreasures(G, my_player, "hand");
        decTreas = numTreasures(G, my_player, "deck");
        discTreas = numTreasures(G, my_player, "discard");
        init_discard = G->discardCount[my_player];
        init_deck = G->deckCount[my_player];
        
        if ((decTreas > 1) || ((decTreas + discTreas) > 1)) expect_dT=2;
        else if ((decTreas + discTreas) == 1) expect_dT=1;
        else expect_dT = 0;
        
        //play adventurer card in hand
        //pcdAdventurer(G, my_player);
        cardEffect(adventurer, 0, 0, 0, G, 0, NULL);
        
        //get state after play
        act_numTreas = numTreasures(G, my_player, "hand");
        act_discard = G->discardCount[my_player];
        act_deck = G->deckCount[my_player];
        
        deltaDK = act_deck - init_deck;
        expect_dD = -(deltaDK + expect_dT);
        deltaT = act_numTreas - init_numTreas;
        deltaD = act_discard - init_discard;
        
        
        if (deltaT == expect_dT) {
          pass_Treas++;
        } else {
          fail_Treas++;
          printf("Test%d delta treas act:%d expected:%d\n", testrun, deltaT, expect_dT);
        }
        
        if (deltaD == expect_dD) {
          pass_Discard++;
        } else {
          fail_Discard++;
          printf("Test%d delta discard act:%d expected:%d\n", testrun, deltaD, expect_dD);
        }
	  }  
	}
	// output summary results
	printf("Tests run: %d   numTreas PASS: %d       numTreas FAIL: %d\n", testrun, \
	pass_Treas, fail_Treas);
	printf("Tests run: %d   numDiscard PASS: %d     numDiscard FAIL: %d\n", testrun, \
	pass_Discard, fail_Discard);
		
	return 0;
}
