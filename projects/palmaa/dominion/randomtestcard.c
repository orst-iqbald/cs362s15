/* -----------------------------------------------------------------------
 * random test for play card village in dominion.c
 * Include the following lines in your makefile:
 *
 * randomtestcard:randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
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



int main() {
    
    struct gameState *G;
    int i, r;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, \
     remodel, smithy, village, baron, great_hall};
	
	// comp value holders
	int init_hand, act_hand, deltaHand;
	int init_discard, act_discard, deltaDiscard;
	int init_deck, act_deck, deltaDeck;
	int init_action, act_action, deltaAction;

	// keep track of number pass/fails
	int pass_Deck=0, fail_Deck=0;
	int pass_Discard=0, fail_Discard=0;
	int pass_Hand=0, fail_Hand=0;
	int pass_Action=0, fail_Action=0;
	
	int testrun = 0;
	    
    printf ("RANDOM ? TESTING village card play\n");
    
    G = newGame();
    
    for (i=0; i < NUMTESTS; i++) {
      //initialize game
      r = initializeGame(PLAYERS, kingdomCards, rand(), G);
      if (r==0) { //only proceed if initialization okay
        testrun++; //increment test run
        
        
        //get initial state 
        int my_player = G->whoseTurn;
        init_hand = G->handCount[my_player];
        init_action = G->numActions;
        init_discard = G->discardCount[my_player];
        init_deck = G->deckCount[my_player];
        
        //play adventurer card in hand
       // pcdAdventurer(G, my_player);
        //cardEffect(village, 0, 0, 0, G, 2, NULL);
        cardEffect(village, 1, 1, 1, G, 4, NULL);
        
        //get state after play
        act_hand = G->handCount[my_player];
        act_action = G->numActions;
        act_discard = G->discardCount[my_player];
        act_deck = G->deckCount[my_player];
        
        deltaDeck = act_deck - init_deck;
        deltaHand = act_hand - init_hand;
        deltaAction = act_action - init_action;
        deltaDiscard = act_discard - init_discard;
        
        
        if (deltaDeck == -1) {
          pass_Deck++;
        } else {
          fail_Deck++;
          printf("Test%d delta deck act:%d expected:%d\n", testrun, deltaDeck, -1);
        }
        if (deltaAction == 2) {
          pass_Action++;
        } else {
          fail_Action++;
          printf("Test%d delta action act:%d expected:%d\n", testrun, deltaAction, 2);
        }
        if (deltaHand == 0) {
          pass_Hand++;
        } else {
          fail_Hand++;
          printf("Test%d delta hand act:%d expected:%d\n", testrun, deltaHand, 0);
        }
        if (deltaDiscard == 1) {
          pass_Discard++;
        } else {
          fail_Discard++;
          printf("Test%d delta discard act:%d expected:%d\n", testrun, deltaDiscard, 1);
        }
	  }  
	}
	// output summary results
	printf("Tests run: %d   numAction PASS: %d       numAction FAIL: %d\n", testrun, \
	pass_Action, fail_Action);
	printf("Tests run: %d   numDiscard PASS: %d     numDiscard FAIL: %d\n", testrun, \
	pass_Discard, fail_Discard);
	printf("Tests run: %d   numHand PASS: %d     numHand FAIL: %d\n", testrun, \
	pass_Hand, fail_Hand);
	printf("Tests run: %d   numDeck PASS: %d     numDeck FAIL: %d\n", testrun, \
	pass_Deck, fail_Deck);
		
	return 0;
}
