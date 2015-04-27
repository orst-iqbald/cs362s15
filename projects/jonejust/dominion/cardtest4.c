///////////////////////////////////////////////////////////////////////////////
// cardtest4.c - VILLAGE CARD EFFECT TEST
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// cardtest4: cardtest4.c dominion.o rngs.o
// 	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)
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

// returns the total number of cards in the deck (treasure cards AND nontreasure)
int totalCards( int curP, struct gameState *g);

// returns number of "cardType" in the curP's hand
int numOfCardType( int curP, struct gameState *g, int cardType );

// runs a single test by running card effect with adventure card
void villageTest( int curP, struct gameState * g, int handPos);


int initializeTest(int numPlayer, int kingdomCards[], int seed,
		struct gameState *state, int maxHandCount);

int main() {

	int i, success;
	int maxHandCount = 8;
	int randHandCount = 0; // will randomize hand count for each test
	int randHandPos = 0; // randomize hand position for each test
	int randCurP = 0; // randomize current player for each test
	int seed = 234;
	int numPlayer = 4;
	int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
		mine, great_hall, ambassador, sea_hag};
	struct gameState game;

	int randAction = 0;

	// set up for number of actions player already has between 1 and 3
	// Player must have at least one action to use card
	for ( i = 1; i <= 3; i++ ) {

		success = initializeTest( numPlayer, k, seed, &game, 5 );
		if ( success == -1 ) {
			printf("There was a problem setting up the test.");
		}

		// let number of cards in hand be semi-random between 1
		// and 8
		randHandCount = (rand() % maxHandCount) + 1;
		randHandPos = rand() % randHandCount; // random pos from # of cards
		// pick a random hand position for village card
		randCurP = rand() % numPlayer; 
		// put village card in handPos where it will be played
		game.hand[randCurP][randHandPos] = village;
		// randomly set number of actions player already has between 1 and 3
		// Player must have at least one action or they wouldn't be able
		// to play card
		randAction = (rand() % 3) + 1;
		game.numActions = randAction;

		// call remodel Effect test with these values
		villageTest( randCurP, &game, randHandPos );
	}
	return 0;


}


// VILLAGE card test function 
// 1. Makes sure number of actions is incremented by two from where they began
// 2. Makes sure number of cards in hand stay the same
void villageTest( int curP, struct gameState * g, int handPos ) {

	int success = -5;
	int preNumActions = 0;
	int postNumActions = 0;
	int preHandCards = 0;
	int postHandCards = 0;

	// set up conditions for test
	g->whoseTurn = curP; // set current player just in case this matters

	// check counts of different kinds of cards in hand, deck and discard
	// before adventurer card
	preNumActions = g->numActions;
	preHandCards = g->handCount[curP];

	// call VILLAGE card effect function
	success = villageEffect( curP, g, handPos);

	///////////////////////////////////////////////////////////////////////////
	// CHECK THAT NUMBER OF ACTIONS IS INCREMENTED BY 2
	///////////////////////////////////////////////////////////////////////////
	postNumActions = g->numActions;
	if ( preNumActions + 2 != postNumActions) {
#if (FAILED_TESTS == 1)
		printf("VILLAGE FAILED to increment actions by 2.\n");
		printf("    Village returned: %d, Actions: %d, Expected: %d\n\n",
				success, postNumActions, preNumActions);
#endif
	}
	else {
#if (PASSED_TESTS == 1)
		printf("VILLAGE PASSED in incrementing actions by 2 when starting with %d actions.\n",
				preNumActions);
#endif
	}
#if (ASSERTION_TESTS ==1)
	assert( preNumActions + 2 == postNumActions);
#endif



	///////////////////////////////////////////////////////////////////////////
	// MAKE SURE NUMBER OF CARDS IN THE HAND STAY THE SAME
	// Village should be removed and another card drawn
	///////////////////////////////////////////////////////////////////////////
	postHandCards = g->handCount[curP];
	if (preHandCards != postHandCards) {
#if (FAILED_TESTS==1)
		printf("VILLAGE FAILED in NOT keeping hand count the same.\n");
		printf("    Village returned: %d, Hand Count: %d, Expected: %d\n\n",
				success, postHandCards, preHandCards);
#endif
	}
	else {
#if (PASSED_TESTS==1)
		printf("VILLAGE PASSED in keeping hand count the same when hand count %d\n",
				preHandCards);
#endif
	}	

#if (ASSERTION_TESTS ==2)
	assert( preHandCards == postHandCards);
#endif
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


// returns the number of cards in deck, discard and hand. This should remain unchanged
int totalCards( int curP, struct gameState *g) {

	int total = 0;
	total = g->discardCount[curP] + g->deckCount[curP] + g->handCount[curP];
	return total;
}

int numOfCardType( int curP, struct gameState *g, int cardType ) {

	int count;
	int i;
	for (i=0; i < g->handCount[curP]; i++ ) {
		if ( g->hand[curP][i] == cardType ) {
			count++;
		}
	}
	return count;
}

int cardTypeDiscardPile( int curP, struct gameState *g, int cardType) {

	int count;
	int i;
	for (i=0; i < g->discardCount[curP]; i++ ) {
		if ( g->discard[curP][i] == cardType ) {
			count++;
		}
	}
	return count;
}
