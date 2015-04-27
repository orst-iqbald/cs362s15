///////////////////////////////////////////////////////////////////////////////
// cardtest1.c - SMITHY CARD EFFECT TEST
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// unittest1: cardtest1.c dominion.o rngs.o
// 	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h" // needed for initializing the game
#include <assert.h>
#include <string.h>
#include <math.h>

// set FAILED_TESTS to 1 for printing tests that fail
#define FAILED_TESTS 1

// set PASSED_TESTS to 1 for printing tests that passed
#define PASSED_TESTS 1

// set ASSERTION_TESTS TO 1 IF WE WANT THOSE TO QUIT THE PROGRAM WHEN NOT TRUE
#define ASSERTION_TESTS 1


void smithyCardTest( int curP, struct gameState * g, int handPos, int begHanCnt,
		int begDecCnt, int begDisCnt );


int initializeTest(int numPlayer, int kingdomCards[], int seed,
		struct gameState *state, int maxHandCount);

// returns number of Smithy cards in a hand
int numSmithyInHand( int curP, struct gameState *g);


int main() {

	// 1. See what happens when (deck count + discard pile) >= 3
	// 2. Check deck count = -4, -3, -2 -1, 0, 1, 2, 3
	// 3. Check discard count = -2, -1, 0, 1, 2, 3 in combination with 
	//    all values from #2   

	int i, j, success;
	int maxHandCount = 8;
	int randHandCount = 0; // will randomize hand count for each test
	int randHandPos = 0; // randomize hand position for each test
	int randCurP = 0; // randomize current player for each test
	int seed = 234;
	int numPlayer = 4;
	int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
		mine, great_hall, ambassador, sea_hag};
	struct gameState game;

	// set up for loop where i is number of cards in deck
	for ( i = 0; i < 5; i++ ) {
		// set up for loop for number of cards in discard pile. We
		// will test with at least 3 because anything less will
		// fail when deck + discard less than 3. This is already known.
		for ( j = 3; j < 8; j++ ) {

			success = initializeTest( numPlayer, k, seed, &game, 5 );
			if ( success == -1 ) {
				printf("There was a problem setting up the test.");
			}

			// let number of cards in hand be random
			randHandCount = (rand() % maxHandCount) + 1;
			randHandPos = rand() % randHandCount; // random pos from # of cards
			randCurP = rand() % numPlayer;
			// need to make sure Smithy is in the right hand position to be played
			// so we can check if it is also discarded
			game.hand[randCurP][randHandPos] = smithy; 

			// call Smithy Effect test with these values
			smithyCardTest( randCurP, &game, randHandPos, randHandCount, i, j);
		}


	}
	return 0;
}


// Smithy card test function 
//
// We want to test under the following different conditions: 
//
//
// After the test we want to check the following: 
// 1. hand count of CURRENT PLAYER should be incremented by 3 for new cards
// 2. if deck count not decremented by 3 THEN:
// 	a) discard pile should be exactly 1 because it means we have had
// 	   a reshuffle.
// 	b) (deck count + previous state of discard pile) should have been decremented by 3
// 3. if deck count was decremented by 3, THEN:
// 	a) discard pile should be incremented by 1 for return of smithy
void smithyCardTest( int curP, struct gameState * g, int handPos, int begHanCnt,
		int begDecCnt, int begDisCnt ) {

	// set up conditions for test
	g->whoseTurn = curP; // set current player just in case this matters
	g->handCount[curP] = begHanCnt;
	g->deckCount[curP] = begDecCnt;
	g->discardCount[curP] = begDisCnt; 


	// int preSmithy = 0;
	// int postSmithy = 0;
	// preSmithy = numSmithyInHand(curP, g);


	// call smithy card effect function
	smithyEffect( curP, g, handPos);

	///////////////////////////////////////////////////////////////////////////
	// CHECK CURRENT PLAYER HANDCOUNT
	// note that the ending hand count should be +2 of the beginning handcount
	// this is because we draw 3 from deck, and discard 1 (the smithy)
	///////////////////////////////////////////////////////////////////////////
	if ( g->handCount[curP] != begHanCnt + 2 ) {
#if (FAILED_TESTS == 1)
		printf("SMITHY FAILED to increment curP handcount when:\n");
		printf("    initial hand count: %d\n", begHanCnt);
		printf("    initial deck count: %d\n", begDecCnt);
		printf("    initial discard count: %d\n", begDisCnt);
		printf("    Ending hand count: %d, Expected: %d\n\n", g->handCount[curP], begHanCnt +2);
#endif
	}
	else {
#if (PASSED_TESTS == 1)
		printf("SMITHY PASSED incrementing handcount when HC: %d, DeckC: %d, DisC: %d\n",
				begHanCnt, begDecCnt, begDisCnt);
#endif
	}
#if (ASSERTION_TESTS == 1)
	assert( g->handCount[curP] == begHanCnt + 2);
#endif


	///////////////////////////////////////////////////////////////////////////
	// CHECK CURRENT PLAYER DISCARD & DECK COUNTS
	///////////////////////////////////////////////////////////////////////////
	//First check when beginning Deckcount is less than three. In this situation
	// the discard pile should end up with exactly 1 card AND deck count +
	// discard pile should be 3 less than initial state.
	//
	if ( begDecCnt < 3 ) {
		// check that (deck count + discard count) was decremented by 3
		// because in this case the discard pile ends up in the deck
		if ( (begDecCnt + begDisCnt - 3) != (g->deckCount[curP] + g->discardCount[curP]) ) {
#if (FAILED_TESTS ==1)
			printf("SMITHY FAILED deck + discard count when:\n");
			printf("    initial hand count: %d\n", begHanCnt);
			printf("    initial deck count: %d\n", begDecCnt);
			printf("    initial discard count: %d\n", begDisCnt);
			printf("    Ending discard count: %d\n", g->discardCount[curP]);
			printf("    Ending deck count: %d\n", g->deckCount[curP]);
			printf("    Deck + Discard: %d, Expected: %d\n\n",
					g->deckCount[curP] + g->discardCount[curP], begDecCnt + begDisCnt - 3);
#endif
		}
		else {
#if (PASSED_TESTS == 1)
			printf("SMITHY PASSED discard count + deck count - 3 test when HC: %d, DeckC: %d, DisC: %d\n",
					begHanCnt, begDecCnt, begDisCnt);
#endif
#if (ASSERTION_TESTS == 1)
		assert( (g->deckCount[curP] + g->discardCount[curP]) == (begDecCnt + begDisCnt - 3) );
#endif
		}
	}
	// Now handle the case where deck count >= 3 and make sure deck count decremented by 3 AND
	// discard count is incremented by 1
	else {
		// First make sure deck count decremented by 3
		if ( g->deckCount[curP] != begDecCnt - 3 ) {
#if (FAILED_TESTS == 1)
			printf("SMITHY FAILED deck count when:\n");
			printf("    initial hand count: %d\n", begHanCnt);
			printf("    initial deck count: %d\n", begDecCnt);
			printf("    initial discard count: %d\n", begDisCnt);
			printf("    Deck: %d, Expected: %d\n\n",
					g->deckCount[curP], begDecCnt - 3);
#endif
		}
		else {
#if (PASSED_TESTS == 1)
			printf("SMITHY PASSED deck count test when HC: %d, DeckC: %d, DisC: %d\n",
					begHanCnt, begDecCnt, begDisCnt);
#endif
		}
#if (ASSERTION_TESTS ==1)
		assert( g->deckCount[curP] == begDecCnt -3 );
#endif
	}


/* The below test has been excluded nitil a better way to count smithy cards can
 * be determined. In order to test this we would also need to count smithy's in 
 * the deck and discard pile and compare all to see where they are moving. 
 * As written right now the test will fail even if there isn't a problem because
 * a smithy could be one of the three cards drawn. 
	///////////////////////////////////////////////////////////////////////////
	// MAKE SURE SMITHY CARD IS DISCARDED
	// (Will do this by making sure the number of smithy cards in the hand
	// is the same before and after a Smithy is played)
	///////////////////////////////////////////////////////////////////////////
	postSmithy = numSmithyInHand(curP, g);
	if ( preSmithy - 1 != postSmithy) {
#if (FAILED_TESTS ==1) 
		printf("SMITHY FAILED to decrement Smithy in hand by 1.\n");
		printf("    initial hand count: %d\n", begHanCnt);
		printf("    initial deck count: %d\n", begDecCnt);
		printf("    initial discard count: %d\n", begDisCnt);
		printf("    NumOfSmithy: %d, Expected %d\n\n", postSmithy, preSmithy -1);
#endif
	}
	else {
#if (PASSED_TESTS ==1)
		printf("SMITHY PASSED in decrementing number of Smithy in hand by 1.\n");
#endif
	}
#if (ASSERTION_TESTS ==1)
	assert( preSmithy - 1 == postSmithy);
#endif
*/
}

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
			temp = rand() % 10;
			state->hand[n][m] = kingdomCards[temp];
		}
	}

	return 0;
}


int numSmithyInHand( int curP, struct gameState *g) {

	int count = 0;
	int i;
	for ( i=0; i < g->handCount[curP]; i++) {

		if ( g->hand[curP][i] == smithy ) {
			count++;
		}
	}
	return count;
}


