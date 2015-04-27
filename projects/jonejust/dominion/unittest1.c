///////////////////////////////////////////////////////////////////////////////
// UNIT TEST#1 - discardCard FUNCTION
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// unittest1: unittest1.c dominion.o rngs.o
// 	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h" // needed for initializing the game
#include <assert.h>
#include <string.h>
#include <math.h>

// set FAILED TESTS TO 1 to print failed tests
#define FAILED_TESTS 1

// set PASSED_TESTS to 1 if we want to print passed tests
#define PASSED_TESTS 1

// set ASSERTION_TESTS TO 1 if we want asserttions to stop program, set if
// ASSSERTION TEST statments that failed below to 2
#define ASSERTION_TESTS 1



int initializeTest(int numPlayer, int kingdomCards[], int seed,
    struct gameState *state, int maxHandCount) {

    int n, m, success, temp;
    // initialize game
    success = initializeGame(numPlayer, kingdomCards, seed, state);
    if ( success == -1)
	return -1; // initializeGame function failed

    // clear players hands and make sure they have 5 random cards. Ensuring
    // randomization will make it easier to find out if the right card
    // is being removed from the hand and put in discard pile later.
    for ( n = 0; n < numPlayer; n++ ) {
	// first clear player's hand
	memset(state->hand[n], '\0', sizeof(int) * state->handCount[n]);
	state->handCount[n] = 0;
	// next draw five cards, and ensure they are random
	for ( m = 0; m < maxHandCount; m++) {
	    success = drawCard(n, state);
	    if (success == -1)
		return -1; // drawcard failed
	    // ensure the card drawn is random
	    temp = floor( Random() * 10 );
	    state->hand[n][m] = kingdomCards[temp];
	}
    }

    // Assert that all the players have 5 cards in their hands to
    // ensure the test is set up properly. 
    for ( n = 0; n < numPlayer; n++ ) {
#if (PASSED_TESTS == 1)
	printf("Player%d cards: %d\n", n, state->handCount[n]);
#endif
#if (ASSERTION_TESTS == 1)
	assert(state->handCount[n] == maxHandCount); // make sure test set up correctly
#endif
    }
    return 0;
}

int main() {

    int currentPlayer, p2;
    int c, d, f, success;
    int card, handPos;
    int preHandCount, postHandCount, preDiscardCount, postDiscardCount;
    int seed = 893;
    int numPlayer = 2;
    int trashFlag = 0;
    int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
	mine, great_hall, ambassador, sea_hag};
    struct gameState game;
    struct gameState pre;
    int maxHandCount = 5; // we will test for handcounts of 1 to 5


    ///////////////////////////////////////////////////////////////////////////
    // 1. TEST DISCARD FUNCTION WITH AND WITHOUT THE TRASHFLAG SET
    ///////////////////////////////////////////////////////////////////////////
  for ( trashFlag = 0; trashFlag < 2; trashFlag++) {

     
    // Next we will set up a loop to check discardCard function on all
    // players
    for ( currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++ ) {
	
	// initialize a game
	// NOTE: The initialize game function is currently set to draw 5 cards for 
	// the first player only. This could change but this is how it is set up at 
	// the time of writing this code so we are calling the initializeTest
	// function which is a wrapper around the initializegame function
	// and makes sure each player has maxHandCount cards. 
	success = initializeTest(numPlayer, k, seed, &game, maxHandCount);
	if (success == -1) {
	    printf("Initialization of test failed.\n");
#if (ASSERTION_TESTS == 1)
	assert( success == 1 );
#endif
	    return -1;
	}


	// Next we set up a loop so that we can check the discardCard
	// function with handCounts from 1 to maxHandCount
	for ( c = maxHandCount; c > 0; c-- ) {
	
	    // next we will randomly select a hand position to 
	    // discard a card from
	    handPos = floor( Random() * c );

	    if ( currentPlayer == 1) 
		p2 = 0;
	    else 
		p2 = 1;

	    // save the gameState before calling the discard function
	    memcpy(&pre, &game, sizeof(struct gameState));

	    // save the card that we will be discarding
	    card = game.hand[currentPlayer][handPos];

	    // save the number of this card in the current hand.
	    // if we are discarding a smithy for example, and there are
	    // two smithys we want to make sure there is 1 smithy in the
	    // hand after we discard it.
	    preHandCount = 0;
	    for ( d = 0; d < c; d++ ) {
		if ( card == game.hand[currentPlayer][d] )
		    preHandCount++;
	    }

	    // Save the number of this card in the discard pile
	    preDiscardCount = 0; // this is not the total # of cards, only the total of type to be dicarded
	    for ( d = 0; d < game.discardCount[currentPlayer]; d++ ) { 
		if ( card == game.discard[currentPlayer][d] ) 
		    preDiscardCount++;
	    }
	

	    // call discardCard function on handPos and without trashflag set
	    discardCard(handPos, currentPlayer, &game, trashFlag);

	    // check discard pile of every player and make sure all are the 
	    // same except for player p who should have their discard pile
	    // incremented by one.
	    for ( p2 = 0; p2 < numPlayer; p2++) {
	        // check to see if current player's discard pile is
	        // properly incremented by 1
	        if ( p2 == currentPlayer ) {

		    if ( game.discardCount[p2] != pre.discardCount[p2] + 1 ) {
#if (FAILED_TESTS == 1)
			printf("DISCARD CARD FAILED discard Count test of current player(%d).\n", p2);
			printf("    Failed at handPos %d with initial handcount of %d\n", handPos, pre.handCount[currentPlayer]); 
			printf("    Resulting discard Count: %d, Expected: %d, Trashflag: %d\n\n",
		   	    game.discardCount[p2], pre.discardCount[p2] + 1, trashFlag);
#endif
		    }
		    else {
#if (PASSED_TESTS ==1)
			printf("DISCARD CARD PASSED discard count test of current player(%d).\n", p2);
			printf("    Passed at handpos %d and initial handcount of %d.\n",
			    handPos, pre.handCount[currentPlayer]);
#endif
		    }
#if (ASSERTION_TESTS == 2)
		    assert( game.discardCount[p2] == (pre.discardCount[p2] + 1) );
#endif
		}
		else {
		    if (game.discardCount[p2] != pre.discardCount[p2]) {		
#if (FAILED_TESTS == 1)
			printf("DISCARD CARD FAILED discard count test other player(%d).\n", p2);
			printf("    Failed  at handPos %d with initial handcount of %d.\n", handPos, pre.handCount[currentPlayer]); 
			printf("    Resulting discard count %d, Expected: %d, Trashflag: %d\n\n",
		            game.discardCount[p2], pre.discardCount[p2], trashFlag);
#endif
		    }
		    else {
#if (PASSED_TESTS == 1)
			printf("DISCARD CARD PASSED discard count test for other player(%d).\n", p2);
			printf("    Passed at handPos %d with initial handcount of %d\n", 
			    handPos, pre.handCount[currentPlayer]);
#endif
		    }
#if (ASSERTION_TESTS == 1)
		    assert( game.discardCount[p2] == pre.discardCount[p2] );
#endif

		}
	    }

	    // check hand count of each player. Current should be decremented 
	    // by one and others should be the same.
	    for ( p2 = 0; p2 < numPlayer; p2++ ) {
		if ( p2 == currentPlayer ) {
		    if ( game.handCount[p2] != pre.handCount[p2] - 1 ) {
#if (FAILED_TESTS == 1)
			printf("DISCARD CARD FAILED for hand count of current player (%d).\n", p2);
			printf("    Discarded handPos %d of current player with initial handcount of %d.\n", handPos, pre.handCount[currentPlayer]);
			printf("    Resulting hand count: %d, Expected: %d, Trashflag: %d\n\n",
			    game.handCount[p2], pre.handCount[p2] -1, trashFlag );
#endif
		    }
		    else {
#if (PASSED_TESTS)
			printf("DISCARD CARD PASSED hand count test of current player (%d).\n", p2);
			printf("    Discarded handPos %d of current player with initial handcount of %d.\n",
			    handPos, pre.handCount[currentPlayer]);
#endif
		    }
#if (ASSERTION_TESTS == 1)
		    assert( game.handCount[p2] == (pre.handCount[p2] -1) );
#endif
		}
		else {
		    if ( game.handCount[p2] != pre.handCount[p2] ) {
#if (FAILED_TESTS == 1)
			printf("DISCARD CARD FAILED hand count test of other player(%d).\n", p2);
			printf("    Discarded handPos %d of current player with initial handCount of %d.\n", handPos, pre.handCount[currentPlayer]);
			printf("    Resulting hand count: %d, Expected: %d, Trashflag: %d\n\n",
			    game.handCount[p2], pre.handCount[p2], trashFlag );
#endif
		    } 
		    else {
#if (PASSED_TESTS ==1)
			printf("DISCARD CARD PASSED hand count test of other player(%d).\n", p2);
			printf("    Discarded handPos %d of current player with initial handCount of %d.\n",
			    handPos, pre.handCount[currentPlayer]);
#endif
		    }
#if (ASSERTION_TESTS == 1)
		    assert( game.handCount[p2] == (pre.handCount[p2]) );
#endif
		}
	    }

	    // check Deck count of every player and make sure deck count
	    // is the same for every player
	    for ( p2 = 0; p2 < numPlayer; p2++ ) {
		if ( p2 == currentPlayer ) {
		    if ( game.deckCount[p2] != pre.deckCount[p2] ) {
#if (FAILED_TESTS == 1)
			printf("DISCARD CARD FAILED for deck count current player(%d).\n", p2);
			printf("    Discarded handPos %d with initial hand count of %d.\n", handPos, pre.handCount[currentPlayer]);
			printf("    Resulting deck count: %d, Expected: %d, Trashflag: %d\n\n",
			    game.deckCount[p2], pre.deckCount[p2], trashFlag );
#endif 
		    }
		    else {
#if (PASSED_TESTS == 1)
			printf("DISCARD CARD PASSED for deck count current player(%d).\n", p2);
#endif
		    }
#if (ASSERTION_TESTS==1)
		    assert( game.deckCount[p2] == pre.deckCount[p2] );
#endif
		}
		else {
		    if ( game.deckCount[p2] != pre.deckCount[p2] ){
#if (FAILED_TESTS == 1)
			printf("DISCARD CARD FAILED for deck count other player (%d).\n", p2);
			printf("    Discarded handPos %d with initial hand count of %d.\n", handPos, pre.handCount[currentPlayer]);
			printf("    Resulting deck count: %d, Expected: %d, Trashflag: %d\n\n",
			    game.deckCount[p2], pre.deckCount[p2], trashFlag );
#endif 	
		    }
		    else {
#if (PASSED_TESTS)
			printf("DISCARD CARD PASSED for deck count other player (%d).\n", p2);
			printf("    Discarded handPos %d with initial hand count of %d.\n", handPos, pre.handCount[currentPlayer]);
#endif
		    }
		}
#if (ASSERTION_TESTS == 1)
		assert( game.deckCount[p2] == (pre.deckCount[p2]) ); 
#endif
	    }


	    // check that the number of cards of the type we discarded is one 
	    // less in the hand count of the current player. If it was 1, it 
	    // should be zero now. If it was 2 before, it should be one now, etc.
	    postHandCount = 0;
	    for ( f = 0; f < game.handCount[currentPlayer]; f++ ) {
		if ( card == game.hand[currentPlayer][f] )
		    postHandCount++;
	    }

	    if ( postHandCount != preHandCount - 1) {
#if (FAILED_TESTS)
		printf("DISCARD CARD FAILED for number of type discarded left in current player %d's hand.\n", currentPlayer);
		printf("    Discarded handPos %d of current player with initial handCount of %d.\n", handPos, pre.handCount[currentPlayer]);
		printf("    Resulting discarded card type in hand: %d, Expected: %d, Trashflag: %d\n\n", 
		    postHandCount, preHandCount -1, trashFlag );
#endif
	    }
	    else {
#if (PASSED_TESTS == 1)
		printf("DISCARD CARD PASSED for number of type discarded left in current player %d's hand.\n", currentPlayer);
		printf("    Discarded handPos %d of current player with initial handCount of %d.\n", handPos, pre.handCount[currentPlayer]);
#endif
	    }
#if (ASSERTION_TESTS == 1)
	    assert( postHandCount == (preHandCount - 1) );
#endif

	    // confirm that the discarded card was put in the discarded pile
	    // and not trashed for example. 
	    for ( f = 0; f < game.discardCount[currentPlayer]; f++ ) {
		if ( card == game.discard[currentPlayer][f] )
		    postDiscardCount++;
	    }

	    if (postDiscardCount != preDiscardCount + 1 ) {
#if (FAILED_TESTS == 1)	    
		printf("DISCARD CARD FAILED for number of card type in current player %d's discard pile.\n", currentPlayer);
		printf("    Discarded handPos %d of current player wtih initial handCount of %d.\n", handPos, pre.handCount[currentPlayer]);
		printf("    Resulting discarded card type in discard pile: %d, Expected: %d, Trashflag: %d\n\n", 
		        postDiscardCount, preDiscardCount + 1, trashFlag );
#endif
	    }
	    else {
#if (PASSED_TESTS ==1)
		printf("DISCARD CARD PASSED for number of card type in current player %d's discard pile.\n", currentPlayer);
		printf("    Discarded handPos %d of current player wtih initial handCount of %d.\n", handPos, pre.handCount[currentPlayer]);
#endif
	    }
#if (ASSERTION_TESTS == 2)
	    assert( postDiscardCount == (preDiscardCount + 1) );
#endif
	}
    }
  }

  return 0;

}




