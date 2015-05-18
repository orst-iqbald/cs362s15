///////////////////////////////////////////////////////////////////////////////
// randomtestcard.c - REMODEL CARD EFFECT TEST
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// randomtestcard.c: randomtestcard.c dominion.o rngs.o
// 	gcc -o randomtestcard randomtestcard.c dominion.o rngs.o $(CFLAGS)
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

// returns number of "cardType" in the curP's discard pile
int cardTypeDiscardPile( int curP, struct gameState *g, int cardType);

// runs a single test by running card effect with adventure card
void remodelTest( int curP, struct gameState * g, int handPos,
		int choice1, int choice2 );

int initializeTest(int numPlayer, int kingdomCards[], int seed,
		struct gameState *state);

int main() {

	// things to test
	// 1. See what happens when (deck count + discard pile) >= 3
	// 2. Check deck count = -4, -3, -2 -1, 0, 1, 2, 3
	// 3. Check discard count = -2, -1, 0, 1, 2, 3 in combination with 
	//    all values from #2   

	int randRemodelHandPos;
	int randCurP = 0; // randomize current player for each test
	int numTests = 500;
	int seed = 234;
	int numPlayer = 4;
	int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
		mine, great_hall, ambassador, sea_hag};
	struct gameState game;

	int randChoice1 = 0; // card the player wants to get
	int randChoice2 = 0; // card that will be trashed

	int i;
	for ( i = 0; i < numTests; i++ ) {

		// first initialize a random game state
		randRemodelHandPos = initializeTest(numPlayer, k, seed, &game);

		// pick a random player to play remodel card
		randCurP = rand() % numPlayer;

		// pick a random hand position for choice 2 that is not the randHandPos as
		// randHandPos will be the remodel card being played 
		while (randRemodelHandPos == randChoice1) {
			randChoice1 = rand() % game.handCount[randCurP];
		}

		// randomly choose a card type to gain using randChoice 2
		randChoice2 = rand() % 10; // 10 card types

		// call remodel Effect test with these values
		remodelTest( randCurP, &game, randRemodelHandPos, game.hand[randCurP][randChoice1], k[randChoice2] );

	}

	return 0;


}


// REMODEL card test function 
//
// We want to test under the following different conditions: 
//
//
// After the test we want to check the following: 
// 1. hand count of CURRENT PLAYER should be incremented by 1 card 
//    two treasure cards are added to the hand and the adventurer
//    card is discarded
// 2. number of treasure cards in hand should be incremented by two
void remodelTest( int curP, struct gameState * g, int handPos,
		int cardToGain, int cardToTrash ) {

	int success = 0;
	int preCardToGain = 0;
	int postCardToGain = 0; // this is the card player wishes to gain
	int preCardToTrashHand = 0;
	int postCardToTrashHand = 0; // this is card player wishes to trash
	// int preCardToTrashDiscard = 0;
	// int postCardToTrashDiscard = 0;

	// set up conditions for test
	g->whoseTurn = curP; // set current player just in case this matters

	// check counts of different kinds of cards in hand, deck and discard
	// before adventurer card
	preCardToTrashHand = numOfCardType(curP, g, cardToTrash);
	// preCardToTrashDiscard = cardTypeDiscardPile(curP, g, cardToGain);
	preCardToGain = cardTypeDiscardPile(curP, g, cardToGain);

	// call ADVENTURER card effect function
	success = remodelEffect( curP, g, handPos, cardToTrash, cardToGain);

	///////////////////////////////////////////////////////////////////////////
	// CHECK THAT CARD TO BE GAINED IS INCREMENTED IN DISCARD PILE IF AND ONLY IF
	//( getCost(cardToTrash) + 2 >= getCost(cardToGain)
	//
	// do this by counting number cards of "cardToGain" is one more after
	// if and only if the above relation is satisfied
	///////////////////////////////////////////////////////////////////////////
	postCardToGain = cardTypeDiscardPile(curP, g, cardToGain);
	if ( getCost(cardToTrash) + 2 >= getCost(cardToGain) ) {
		// in this case number of cardToGain should have been incremented
		if ( (preCardToGain + 1 != postCardToGain) && (g->supplyCount[cardToGain] > 0) ) {
			// card wasn't properly incremented and added to hand
#if (FAILED_TESTS ==1)
			printf("REMODEL FAILED to add card new card to discard pile when: \n");
			printf("    Supply count of card to gain: %d\n", g->supplyCount[cardToGain]);
			printf("    Cost of card to gain: %d, Cost of trashed card + 2: %d\n\n",
					getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
		}
		else {
#if (PASSED_TESTS ==1)
			printf("REMODEL PASSED adding card to discard pile when supply: %d, Cost of card to gain: %d, cost of trashed card + 2: %d\n",
					g->supplyCount[cardToGain], getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
		}
#if (ASSERTION_TESTS == 2)
		assert( preCardToGain + 1 == postCardToGain);
#endif
	}

	///////////////////////////////////////////////////////////////////////////
	// MAKE SURE CARD TO BE GAIN NOT INCREMENTED IF 
	// (get Cost (cardToTrash) + 2 < getCost(cardtoGain)
	///////////////////////////////////////////////////////////////////////////
	if ( getCost(cardToTrash) + 2 < getCost(cardToGain) ) {
		// in this case number of cardToGain should NOT have been incremented
		if ( (preCardToGain != postCardToGain) || (g->supplyCount[cardToGain] == 0) ) {
			// type of "cardToGain" in discard pile was changed and it should NOT have been
#if (FAILED_TESTS ==1)
			printf("REMODEL FAILED by incrementing card to be gained in the discard pile when: \n");
			printf("    Supply count of card to gain: %d\n", g->supplyCount[cardToGain]);
			printf("    Cost of card to gain: %d, Cost of trashed card + 2: %d\n\n",
					getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
		}
		else {
#if (PASSED_TESTS ==1) 
			printf("REMODEL PASSED not incrementing card to be gained when supply: %d, Cost of card to gain: %d, cost of trashed card + 2: %d\n",
					g->supplyCount[cardToGain], getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
		}
#if (ASSERTION_TESTS == 0)
		assert( preCardToGain == postCardToGain );
#endif
	}

	///////////////////////////////////////////////////////////////////////////
	// MAKE SURE CARD TO BE TRASHED IS NOT STILL IN HAND AFTER REMODEL CARD 
	///////////////////////////////////////////////////////////////////////////
	postCardToTrashHand = numOfCardType(curP, g, cardToTrash);
	if (preCardToTrashHand - 1 != postCardToTrashHand ) {
		if (success == 0) {
			// remodel returned success but card that was supposed to be 
			// trashed was not trashed. This is a failed test
#if (FAILED_TESTS ==1)
			printf("REMODEL FAILED when remodel returned success but card to trash still in hand.\n");
			printf("    Supply count of card to gain: %d\n", g->supplyCount[cardToGain]);
			printf("    Cost of card to gain: %d, Cost of trashed card + 2: %d\n\n",
					getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
		}
		else {
#if (PASSED_TESTS ==1) 
			printf("REMODEL PASSED test of properly removing trashed card from hand.\n");
#endif
		}
#if (ASSERTION_TESTS == 2)
		assert( preCardToTrashHand - 1 == postCardToTrashHand );
#endif
	}
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


// this function returns -1 upon failure, else returns the 
// handPos of the remodel card which was randomly assigned
int initializeTest(int numPlayer, int kingdomCards[], int seed,
		struct gameState *state) {

	int n, m, success, temp;
	int randHandCount = -1;
	int isInRange = -1;
	int randRemodelHandPos;

	// initialize game
	success = initializeGame(numPlayer, kingdomCards, seed, state);
	if ( success == -1)
		return -1; // initializeGame function failed


	// first randomly assign supply counts to all the kingdom cards
	int randSupplyCount;
	int isBoundarySupply;	


	int x;
	for ( x = 0; x < 10; x++ ) {
		// for kingdom card x first determine randomly if it 
		// should be a boundary case, i.e. supply zero. make
		// boundary cases happen 25% of the time
		isBoundarySupply = rand() % 4;
		if ( isBoundarySupply == 0 ) {
			randSupplyCount = 0;
		}
		else {

			randSupplyCount = 1 + ( rand() % 10 );
		}
		// assign this randomly chosen supply count for card x
		// to supply of card
		state->supplyCount[ kingdomCards[x] ] = randSupplyCount;
	}


	// clear players' hands and make sure they have a remodel card
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
		randRemodelHandPos = rand() % randHandCount;
		state->hand[n][ randRemodelHandPos ] = remodel;

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

	return randRemodelHandPos;
}


