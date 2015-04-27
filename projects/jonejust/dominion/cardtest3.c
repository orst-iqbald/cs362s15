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

    int randChoice1 = 0; // card the player wants to get
    int randChoice2 = 0; // card that will be trashed

    // set up for loop where i will be the supply of cards. Supply of ever card
    // will be set to i
    for ( i = 0; i < 5; i++ ) {
	
	for ( j = 0; j < 10; j++) {
	    game.supplyCount[ k[j] ] = i;
	}

	    success = initializeTest( numPlayer, k, seed, &game, 5 );
	    if ( success == -1 ) {
		printf("There was a problem setting up the test.");
	    }

	    // let number of cards in hand be semi-random:
	    // at least two cards need to be in hand however, one for card
	    // to be trashed and another to play remodel card
	    randHandCount = (rand() % maxHandCount) + 2;
	    randHandPos = rand() % randHandCount; // random pos from # of cards
	    // pick a random hand position for choice 2 that is not the randHandPos as
	    // randHandPos will be the remodel card being played 
	    while (randHandPos == randChoice1) {
		randChoice1 = rand() % randHandCount;
	    }
	    randCurP = rand() % numPlayer; 
	    // put remodel card in handPos where it will be played
	    game.hand[randCurP][randHandPos] = remodel;
	    // randomly choose a card type to gain using randChoice 2
	    randChoice2 = rand() % 10; // 10 card types

	    // call remodel Effect test with these values
	    remodelTest( randCurP, &game, randHandPos, game.hand[randCurP][randChoice1], k[randChoice2] );


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
	    printf("REMODEL PASSED when supply: %d, Cost of card to gain: %d, cost of trashed card + 2: %d\n",
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
	    printf("REMODEL FAILED by incrementing cardToGain in discard pile when: \n");
	    printf("    Supply count of card to gain: %d\n", g->supplyCount[cardToGain]);
	    printf("    Cost of card to gain: %d, Cost of trashed card + 2: %d\n\n",
		getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
	}
	else {
#if (PASSED_TESTS ==1) 
	    printf("REMODEL PASSED when supply: %d, Cost of card to gain: %d, cost of trashed card + 2: %d\n",
		g->supplyCount[cardToGain], getCost(cardToGain), getCost(cardToTrash) + 2);
#endif
	}
#if (ASSERTION_TESTS == 1)
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
/* Test is more complicated than originally thought. Card type to be trashed
 * needs to be compared against card type picked up by remodel card as well
 * before this test can be trusted as a check against whether the card 
 * was propertly trashed or not.
    ///////////////////////////////////////////////////////////////////////////
    // MAKE SURE CARD TO BE TRASHED IS NOT PUT IN DISCARD PILE
    ///////////////////////////////////////////////////////////////////////////
    preCardToTrashDiscard = cardTypeDiscardPile(curP, g, cardToGain);
    if (preCardToTrashDiscard != postCardToTrashDiscard) {
	// number of type of card to trash has changed in the discard pile
	// and that shouldn't have been changed
#if (FAILED_TESTS == 1)
	printf("REMODEL FAILED by changing number of card to trash in the discard pile.\n");
	printf("    Remodel returned: %d, Card type that should have been trashed: %d\n\n",
	    success, cardToTrash);
#endif
    }
    else {
#if (PASSED_TESTS == 1)
	printf("REMODEL PASSED in not changing number of card to trash in discard pile.\n");
#endif
    }
#if (ASSERTION_TESTS == 2)
	assert( preCardToTrashDiscard == postCardToTrashDiscard );
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
