///////////////////////////////////////////////////////////////////////////////
// randomtestaventurer.c - RANDOM ADVENTURER CARD TEST
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// randomtestadventurer.out
// 	gcc -o randomadventurercard randomadventurercard.c dominion.c rngs.c $(CFLAGS)
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
void adventureTest( int curP, struct gameState * g);


int initializeTest(int numPlayer, int kingdomCards[], int seed,
		struct gameState *state, int maxHandCount);

int main() {

	// Things to check for adventurercard
	// 1. See what happens when (deck count + discard pile) >= 3
	// 2. Check deck count = -4, -3, -2 -1, 0, 1, 2, 3
	// 3. Check discard count = -2, -1, 0, 1, 2, 3 in combination with 
	//    all values from #2   

	int success;
	int randCurP = 0; // randomize current player for each test
	int seed = 234;
	int numPlayer = 4;
	int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
		mine, great_hall, ambassador, sea_hag};
	struct gameState game;
	int numTests = 500; // number of random tests we wish to run

	// initialize test with random values for current player, hand counts
	// deck counts and discard counts of all players are all randomly 
	// assigned. Boundary cases were given extra weight in the random
	// assignments so those are more thoroughly tested. See 
	// initializeTest function for details. 
	

	int m;
	for ( m = 0; m < numTests; m++ ) {
	success = initializeTest( numPlayer, k, seed, &game, 5 );
	if ( success == -1 ) {
		printf("There was a problem setting up the test.");
	}

	// let number of cards in hand be semi-random
	// However, it does need to be confirmed that a total of at least
	// two treaasure cards are in the deck or discard pile. Otherwise
	// the adventurer card will not be able to find two treasure cards.
	// This will always be assured by putting at least 2 cards in the
	// discard pile or deck.
	randCurP = rand() % numPlayer;

	// set whose turn it is to the Current player randomly chosen 
	game.whoseTurn = randCurP;

	//game.discard[randCurP][1] = copper;
	// game.discard[randCurP][2] = gold;

	// call Adventurer Effect test with these values
	adventureTest( randCurP, &game);
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
void adventureTest( int curP, struct gameState * g) {


	int preTreas = 0;
	int postTreas = 0;
	int preTotalTreas = 0;
	int postTotalTreas = 0;
	int preTotalCards = 0;
	int postTotalCards = 0;

	// Check the current player's beginning hand count, deck count 
	// and discard count so we can see how it changes after playing the adventure
	// card
	int begHanCnt = g->handCount[curP];
	int begDisCnt = g->discardCount[curP];
	int begDecCnt = g->deckCount[curP];

	// check counts of different kinds of cards in hand, deck and discard
	// before adventurer card. the total treaasure cards in deck and discard
	// count should be decremented after the call to adventurer
	preTreas = countTreasureCards( curP, g);
	preTotalTreas = totalTreas(curP, g);
	preTotalCards = totalCards(curP, g);

	// call ADVENTURER card effect function
	adventurerEffect( curP, g);


	///////////////////////////////////////////////////////////////////////////
	// FIRST CHECK THAT IF DIS
	///////////////////////////////////////////////////////////////////////////


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
		printf("ADVENTURER FAILED incrementing number of treasure cards in hand by two when:\n");
		printf("    initial hand count: %d\n", begHanCnt);
		printf("    initial deck count: %d\n", begDecCnt);
		printf("    initial discard count: %d\n", begDisCnt);
		printf("    Treasure cards: %d, Expected: %d\n", postTreas, preTreas + 2);
#endif
#if (PASSED_TESTS ==1)
		printf("ADVENTURER PASSED incrementing number of treasure cards in hand by two.\n");
#endif
	}
#if (ASSERTION_TESTS ==0)
	assert( preTreas + 2 == postTreas);
#endif


	///////////////////////////////////////////////////////////////////////////
	//CHECK THAT TOTAL TREASURE CARDS IN HAND, DISCARD PILE AND DECK REMAINS
	//THE SAME BEFORE AND AFTER. THIS TOTAL SHOULDN'T CHANGE
	///////////////////////////////////////////////////////////////////////////
	postTotalTreas = totalTreas(curP, g);
	if ( preTotalTreas != postTotalTreas ) {
#if (FAILED_TESTS ==1)
		printf("ADVENTURER FAILED by not keeping total treasure in deck, discard and hand the same when:\n");
		printf("    initial hand count: %d\n", begHanCnt);
		printf("    initial deck count: %d\n", begDecCnt);
		printf("    initial discard count: %d\n", begDisCnt);
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
		printf("    initial hand count: %d\n", begHanCnt);
		printf("    initial deck count: %d\n", begDecCnt);
		printf("    initial discard count: %d\n", begDisCnt);
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

// this function returns the position of the adventurer card upon success 
// or - 1 upon failure
int initializeTest(int numPlayer, int kingdomCards[], int seed,
		struct gameState *state, int maxHandCount) {

	int n, m, success, temp;
	int randHandCount = -1;
	int isInRange = -1;
	int randAdventurerHandPos;

	// initialize game
	success = initializeGame(numPlayer, kingdomCards, seed, state);
	if ( success == -1)
		return -1; // initializeGame function failed

	// clear players' hands and make sure they have an adventurer card
	// and anywhere from 0 to more cards in the hand.
	// randomization will make it easier to find out if the right card
	// is being removed from the hand and put in discard pile later.
	for ( n = 0; n < numPlayer; n++ ) {
		// first clear player's hand and assign a random hand count
		// to the player. Note that the count needs to be at least
		// one as the player will need to play an adventurer card.
		// the isInRange variable will be used and randomly given a 
		// value of zero or 1. If isInRange is 1 then randHandCount
		// will be given a value that is within a more normal range
		// of 1 to 10 cards in the hand. If isInRange is 0 then 
		// a number of 1 to 25 will be assigned to randHandCount
		isInRange = rand() % 2;
		if (isInRange == 1) {
			randHandCount = 1 + (rand() % 10);
		}
		else {
			randHandCount = 1 + (rand() % 25);
		}
		// make hand count variable be the number of cards in the hand
		// (i.e. randHandCount)
		state->handCount[n] = randHandCount;	
		
		memset(state->hand[n], '\0', sizeof(int) * state->handCount[n]);
		// next fill the hand with randHandCount number of cards and
		// have the card types be randomly chosen
		for ( m = 0; m < randHandCount; m++) {
			temp = rand() % 10;
			state->hand[n][m] = kingdomCards[temp];
		}
	
		// now put the adventurer card in a random hand position
		randAdventurerHandPos = rand() % randHandCount;
		state->hand[n][ randAdventurerHandPos ] = adventurer;

		// now set the discardPile for player n. Also guide the randomness
		// toward the boundary cases so we can do some test cases 
		// where both discardCount and deckCount are zero to see 
		// how the adventurer card handles those. Any case where discardCount
		// and deckcount have less than two treasure cards are likely to 
		// provide interesting outcomes as the card won't be able to provide
		// two treasure cards from these decks. it should at least keep the counts
		// of these two decks the same. 
		int startDiscardCount = 0;
		int startDeckCount = 0;
		int isDiscardBoundary = rand() % 4;
		int isDeckBoundary = rand() % 4;
		if ( isDiscardBoundary == 0 ) {
			// do a boundary case by giving discard count
			// a value of zero or 1
			startDiscardCount = rand() % 2;
		}
		// approximately 25% of time make discard Count anything from 
		// 0 to 250, which is max discardCount
		else if (isDiscardBoundary == 3) {
			
			startDiscardCount = rand() % 256;
		}
		// approximately 50% of time give discard Count a more normal range
		// from 10 to 30
		else {

			startDiscardCount = 10 + (rand() % 21);
		}
		state->discardCount[n] = startDiscardCount;
		// now determine deck count
		if ( isDeckBoundary == 0 ) {
			// do a boundary case by giving deck count
			// a value of zero or 1
			startDeckCount = rand() % 2;
		}
		// approximately 25% of time make deck Count anything from 
		// 0 to 250, which is max discardCount
		else if (isDeckBoundary == 3) {
			
			startDeckCount = rand() % 256;
		}
		// approximately 50% of time give Deck Count a more normal range
		// from 10 to 30
		else {

			startDeckCount = 10 + (rand() % 21);
		}
		state->deckCount[n] = startDeckCount;

		// now randomly assign card types to the deck and discard piles.
		int z;
		for ( z = 0; z < startDiscardCount; z++ ) {

			state->discard[n][z] = rand() % 10;
		}
		for ( z = 0; z < startDeckCount; z++ ) {

			state->deck[n][z] = rand() % 10;
		}

	}

	return randAdventurerHandPos;
}


// returns the number of cards in deck, discard and hand. This should remain unchanged
int totalCards( int curP, struct gameState *g) {

	int total = 0;
	total = g->discardCount[curP] + g->deckCount[curP] + g->handCount[curP];
	return total;
}


