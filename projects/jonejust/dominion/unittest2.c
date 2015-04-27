///////////////////////////////////////////////////////////////////////////////
// UNIT TEST#2 - drawCard FUNCTION
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// unittest2: unittest2.c dominion.c rngs.c
// 	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h" // needed for initializing the game
#include <assert.h>
#include <string.h>
#include <math.h>

// set ERROR_RESULTS TO 0 to remove error printf statements from output
#define FAIL_RESULTS 1

// set PASS_RESULTS to 1 to print test results that pass
#define PASS_RESULTS 1

// set ASSERTION_TESTS TO 1 IF WE WANT THOSE TO QUIT THE PROGRAM WHEN NOT TRUE
#define ASSERTION_TESTS 1

int initializeDrawCardTest(int numPlayer, int kingdomCards[], int seed,
    struct gameState *state, int initialDeckCount, int initialDiscardCount ) {

    int n, m, p, success, temp;
    // initialize game
    success = initializeGame(numPlayer, kingdomCards, seed, state);
    if ( success == -1)
	return -1; // initializeGame function failed

    // clear players hands so there hand counts are zero
    for ( n = 0; n < numPlayer; n++ ) {
	// first clear player's hand
	memset(state->hand[n], '\0', sizeof(int) * state->handCount[n]);
	state->handCount[n] = 0;
	// Set the number of cards in the deck to 7, and the number in discard
	// pile to 2. We will be drawing 10 cards from the each player's deck 
	// to ensure that we reach a point where the cards have to be shuffled from the 
	// discard pile again. We will also be starting with a handcount of zero
	// for each player so we can check that boundary case.
	for ( m = 0; m < initialDeckCount; m++ ) {

	    temp = floor( Random() * 10 );
	    state->deck[n][m] =  temp;
	}
	state->deckCount[n] = initialDeckCount;


	// Also want to make sure there are cards in the discard pile so that
	// after drawing all cards from deck during test, there are cards
	// in discard pile that can be shuffled and moved to deck
	for ( p = 0; p < initialDiscardCount; p++ ) {
	    temp = floor( Random() * 10 );
	    state->discard[n][p] = temp;
	    
	}
	state->discardCount[n] = initialDiscardCount;
    }
    return 0;
}


int main() {


    int i, j, success;
    int curPlayer;
    int initialDiscardCount = 100;
    int initialDeckCount = 7;
    int cardsToDraw = 10;
    int seed = 234;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
	mine, great_hall, ambassador, sea_hag};
    struct gameState game;
    struct gameState pre;


    ///////////////////////////////////////////////////////////////////////////
    // 1. TEST DRAW CARD
    ///////////////////////////////////////////////////////////////////////////
    
	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
	    printf("Initialization of test failed.\n");
	    return -1;
	} 

	// test function for different players
	for ( curPlayer = 0; curPlayer < numPlayer; curPlayer++ ) {
	    
	    for ( i = 0; i < cardsToDraw; i++ ) {
		// save game state before calling drawCard function
		memcpy(&pre, &game, sizeof(struct gameState)); 

		// execute drawCard function
		success = drawCard(curPlayer, &game);
		if ( success == -1 ) {
#if (FAIL_RESULTS ==1)
		    printf("DRAW CARD FAILED when drawing for player %d. drawCard function returned -1.\n", curPlayer);
		    printf("    Player: %d deckCount: %d, handCount: %d,\n\n",
			curPlayer, pre.deckCount[curPlayer], pre.handCount[curPlayer]);
#endif
		}
#if (ASSERTION_RESULTS == 1)
		assert( sucess == 0 );
#endif

		// check that handcount of currentPlayer was incremented and no other player
		// had there handcount incremented
		for ( j = 0; j < numPlayer; j++ ) {
		    if ( j == curPlayer) {
			if ( pre.handCount[curPlayer] +1 != game.handCount[curPlayer] ) {
#if (FAIL_RESULTS == 1)
			    printf("DRAW CARD FAILED handcount test for curPlayer %d when deckCount at %d\n",
				curPlayer, pre.deckCount[curPlayer]);
			    printf("    CurPlayer handcount: %d, Expected: %d\n\n",
				game.handCount[curPlayer], pre.handCount[curPlayer] + 1 );
#endif
			}
#if (PASS_TESTS ==1)
			    printf("DRAW CARD PASSED handcount test for curPlayer %d when deckCount at %d\n",
				curPlayer, pre.deckCount[curPlayer]);
#endif
#if (ASSERTION_TESTS == 1)
    			assert(pre.handCount[curPlayer] + 1 == game.handCount[curPlayer] );
#endif
		    }
		    else {
			if ( pre.handCount[j] != game.handCount[j] ) {
#if (FAIL_RESULTS == 1)
			    printf("DRAW CARD FAILED handcount test for another player when curPlayer %d drew.\n", curPlayer);
			    printf("    Player %d handcount changed to: %d, Expected: %d\n\n", j, game.handCount[j], pre.handCount[j]);
#endif
			}
#if (PASS_RESULTS == 1)
			else {
			    printf("DRAW CARD PASSED handcount test for another player when curPlayer %d drew.\n", curPlayer);
			}
#endif
#if (ASSERTION_TESTS == 1)
			assert(pre.handCount[j] == game.handCount[j] );
#endif
		    }
		}

		// check that deckcount was decremented for currentplayer and that deckcount
		// was not decremented or changed for any other player. Also allow for
		// special case where Deckcount is zero and we shuffle in the initialDiscardCount
		// pile such that after drawing a card deck count will be initialDiscardCount - 1
		for ( j = 0; j < numPlayer; j++ ) {
		    if ( j == curPlayer) {
			if ( ( pre.deckCount[curPlayer] - 1 != game.deckCount[curPlayer] ) &&
			    ( pre.deckCount[curPlayer] != 0 ) && ( game.deckCount[curPlayer] != initialDiscardCount -1) ) {
#if (FAIL_RESULTS == 1)
			    printf("DRAW CARD FAILED deck test when curPlayer %d and initial deckCount %d\n",
				curPlayer, pre.deckCount[curPlayer]);
			    if ( pre.deckCount[curPlayer] != 0 ) {
			    printf("    CurPlayer deckcount: %d, Expected: %d\n\n",
				game.deckCount[curPlayer], pre.deckCount[curPlayer] + 1 );
			    }
			    else {
				printf("    CurPlayer deckcount: %d, Discard Count: %d, Expected: %d\n\n",
				    game.deckCount[curPlayer], game.discardCount[curPlayer], initialDiscardCount - 1  ); // because discard pile shuffled in
			    }
#if (ASSERTION_TESTS == 1)
			    assert(pre.deckCount[curPlayer] - 1 == game.deckCount[curPlayer] );
#endif
			}
#endif
#if (PASS_RESULTS)
			else {
			     printf("DRAW CARD PASSED deck test when curPlayer %d and initial deckCount %d\n",
				curPlayer, pre.deckCount[curPlayer]);
			}
#endif
		    }
		    else {
			if ( pre.deckCount[j] != game.deckCount[j] ) {
#if (FAIL_RESULTS == 1)
			    printf("DRAW CARD FAILED deck test of another player when curPlayer %d drew from deckcount %d\n",
				curPlayer, pre.deckCount[curPlayer]);
			    printf("    Player %d deck count changed to: %d, Expected: %d\n\n", j, game.deckCount[j], pre.deckCount[j]);
#endif
			}
			else {
#if (PASS_RESULTS == 1)
			    printf("DRAW CARD PASSED  deck test of another player when curPlayer %d drew from deckcount %d.\n",
				curPlayer, pre.deckCount[curPlayer]);
#endif
			}
#if (ASSERTION_TESTS == 1)
			    assert(pre.deckCount[j] == game.deckCount[j] );
#endif
		    }
		}
	    }
	}

  return 0;

}
