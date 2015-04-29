///////////////////////////////////////////////////////////////////////////////
// cardtest2.c - ADVENTURER CARD EFFECT TEST
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// cardtest2: cardtest2.c dominion.o rngs.o
// 	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
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

// returns number of treasure cards in the hand
int countTreasureCards( int curP, struct gameState *g);
// returns number of treasure cards in deck
int deckTreasCount( int curP, struct gameState *g);
// returns number of treasure cards in discard pile
int discardTreasCount( int curP, struct gameState *g);
// returns number of treasure cards in deck, hand and discard pile combined
int totalTreas( int curP, struct gameState *g);

// returns the total number of cards in the deck (treasure cards AND nontreasure)
int totalCards( int curP, struct gameState *g);

// runs a single test by running card effect with adventure card
void adventureTest( int curP, struct gameState * g, int handPos, int begHanCnt,
    int begDecCnt, int begDisCnt );


int initializeTest(int numPlayer, int kingdomCards[], int seed,
    struct gameState *state, int maxHandCount);

int main() {

 // things to test
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

	    // let number of cards in hand be semi-random
	    // However, it does need to be confirmed that a total of at least
	    // two treaasure cards are in the hand, deck or discard pile. 
	    // The adventurer card will not work if there are not at least
	    // two treasure cards somewhere. We will put two in the discard
	    // pile
	    randHandCount = (rand() % maxHandCount) + 1;
	    randHandPos = rand() % randHandCount; // random pos from # of cards
	    randCurP = rand() % numPlayer; 
	    game.discard[randCurP][1] = copper;
	    game.discard[randCurP][2] = gold;

	    // call Adventurer Effect test with these values
	    adventureTest( randCurP, &game, randHandPos, randHandCount, i, j);
	}


    }
    return 0;


}


// ADVENTURER card test function 
//
// We want to test under the following different conditions: 
//
//
// After the test we want to check the following: 
// 1. hand count of CURRENT PLAYER should be incremented by 1 card 
//    two treasure cards are added to the hand and the adventurer
//    card is discarded
// 2. number of treasure cards in hand should be incremented by two
void adventureTest( int curP, struct gameState * g, int handPos, int begHanCnt,
    int begDecCnt, int begDisCnt ) {


    int preTreas = 0;
    int postTreas = 0;
    int preTotalTreas = 0;
    int postTotalTreas = 0;
    int preTotalCards = 0;
    int postTotalCards = 0;

    // set up conditions for test
    g->whoseTurn = curP; // set current player just in case this matters
    g->handCount[curP] = begHanCnt;
    g->deckCount[curP] = begDecCnt;
    g->discardCount[curP] = begDisCnt;

    // check counts of different kinds of cards in hand, deck and discard
    // before adventurer card
    preTreas = countTreasureCards( curP, g);
    preTotalTreas = totalTreas(curP, g);
    preTotalCards = totalCards(curP, g);

    // call ADVENTURER card effect function
    adventurerEffect( curP, g);

    ///////////////////////////////////////////////////////////////////////////
    // CHECK CURRENT PLAYER HANDCOUNT INCREMENTED BY ONE
    // Two treasure cards are added to the hand, but the adventurer card
    // should also be discarded which should results in an increment of the
    // hand by one.
    ///////////////////////////////////////////////////////////////////////////
    if ( g->handCount[curP] != begHanCnt + 1 ) {
#if (FAILED_TESTS == 1)
	printf("ADVENTURER FAILED to increment curP handcount by 1 when:\n");
	printf("    initial hand count: %d\n", begHanCnt);
	printf("    initial deck count: %d\n", begDecCnt);
	printf("    initial discard count: %d\n", begDisCnt);
	printf("    Ending hand count: %d, Expected: %d\n\n", g->handCount[curP], begHanCnt +1);
#endif
    }
    else {
#if (PASSED_TESTS == 1)
	printf("ADVENTURER PASSED incrementing handcount by 1 when HC: %d, DeckC: %d, DisC: %d\n",
	    begHanCnt, begDecCnt, begDisCnt);
#endif
    }
#if (ASSERTION_TESTS == 2)
    assert( g->handCount[curP] == begHanCnt + 1);
#endif


    ///////////////////////////////////////////////////////////////////////////
    // CHECK THAT TREASURE CARDS IN HAND INCREMENTED BY TWO
    ///////////////////////////////////////////////////////////////////////////
    postTreas = countTreasureCards(curP, g);
    if (preTreas + 2 != postTreas) {
#if (FAILED_TESTS ==1)
	printf("ADVENTURER FAILED incrementing number of treasure cards in hand by two.\n");
	printf("    Treasure cards: %d, Expected: %d\n", postTreas, preTreas + 2);
#endif
#if (PASSED_TESTS ==1)
	printf("ADVENTURER PASSED incrementing number of treasure cards in hand by two.\n");
#endif
    }
#if (ASSERTION_TESTS ==1)
	assert( preTreas + 2 == postTreas);
#endif


    ///////////////////////////////////////////////////////////////////////////
    //CHECK THAT TOTAL TRESURE CARDS IN HAND, DISCARD PILE AND DECK REMAINS
    //THE SAME BEORE AND AFTER. THIS TOTAL SHOULDN'T CHANGE
    ///////////////////////////////////////////////////////////////////////////
    postTotalTreas = totalTreas(curP, g);
    if ( preTotalTreas != postTotalTreas ) {
#if (FAILED_TESTS ==1)
	printf("ADVENTURER FAILED by not keeping total treasure in deck, discard and hand the same.\n");
	printf("    Treasure cards: %d, Expected: %d\n", postTotalTreas, preTotalTreas);
#endif
#if (PASSED_TESTS ==1)
	printf("ADVENTURER PASSED by keeping combined total treaasure in deck, discard and hand unchanged.\n");
#endif
    }
#if (ASSERTION_TESTS ==1)
	assert( preTotalTreas == postTotalTreas);
#endif



    ///////////////////////////////////////////////////////////////////////////
    // CHECK TOTAL NUMBER OF CARDS IN DECK, DISCARD AND HAND 
    // (total of tresure AND nontresure) This should remain unchanged
    ///////////////////////////////////////////////////////////////////////////
    postTotalCards = totalCards( curP, g);
    if ( preTotalCards != postTotalCards) {
#if (FAILED_TESTS == 1)
	printf("ADVENTURER FAILED by not keeping total cards in deck, discard and hand the same.\n");
	printf("   Total Cards: %d, Expected: %d\n", postTotalCards, preTotalCards);
#endif
    }
    else {
#if (PASSED_TESTS ==1)
	printf("ADVENTURER PASSED by keeping combined total cards in deck, discard, and hand the same.\n");
#endif
    }
#if (ASSERTION_TESTS ==1)
    assert( preTotalCards == preTotalCards);
#endif

}



// takes in current player and a game state as a parameter
// returns number of treasure cards in current player's hand
int countTreasureCards( int curP, struct gameState *g) {

    int i;
    int count = 0;
    for (i=0; i < g->handCount[curP]; i++) {
	if ( (g->hand[curP][i] == copper) || (g->hand[curP][i] == silver) ||
	(g->hand[curP][i] == gold) ) {
	    count++;
	}
    }
    return count;
}

int discardTreasCount( int curP, struct gameState *g) {

    int i;
    int count = 0;
    for (i=0; i < g->discardCount[curP]; i++) {
	if ( (g->discard[curP][i] == copper) || (g->discard[curP][i] == silver) ||
	(g->discard[curP][i] == gold) ) {
	    count++;
	}
    }
    return count;

}

int deckTreasCount( int curP, struct gameState *g) {

    int i;
    int count = 0;
    for (i=0; i < g->deckCount[curP]; i++) {
	if ( (g->deck[curP][i] == copper) || (g->deck[curP][i] == silver) ||
	(g->deck[curP][i] == gold) ) {
	    count++;
	}
    }
    return count;

}


// returns total number of treasure cards in discard, deck and hand combined
int totalTreas( int curP, struct gameState *g) {

    int total = 0;
    total = deckTreasCount(curP, g) + discardTreasCount(curP, g) + 
	countTreasureCards( curP, g);
    return total; 
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


