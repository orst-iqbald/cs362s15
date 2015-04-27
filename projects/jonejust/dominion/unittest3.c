//////////////////////////////////////////////////////////////////////////////
// UNIT TEST#3 - gainCard FUNCTION
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// unittest3: unittest3.c dominion.c rngs.c
// 	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
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
	int temp;
	int flag; // used to test flags set to zero, one and two for gainCard
	int curPlayer;
	int initialDiscardCount = 0; // starting here to test boundary of zero for gainCard
	int initialDeckCount = 0; // starting the gain card here to test boundary of zero
	int cardsToDraw = 10;
	int seed = 234;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, smithy, remodel, village,
		mine, great_hall, ambassador, sea_hag};
	struct gameState game;
	struct gameState pre;


	///////////////////////////////////////////////////////////////////////////
	// TEST GAIN CARD COUNTS
	///////////////////////////////////////////////////////////////////////////
	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
		printf("Initialization of test failed.\n");
		return -1;
	} 

	// set up the supply counts of each card in the game to 10
	for ( i = 0; i < 10; i++ ) {
		game.supplyCount[ k[i] ] = 10;
	} 


	// set up a loop to test gainCard for each separate flag:
	// Flag set to 0: should add card to discard pile
	// set to 1: should add to deck
	// set to 2: should add to hand
	for ( flag = 0; flag < 3; flag++ ) {
		// test function for different players
		for ( curPlayer = 0; curPlayer < numPlayer; curPlayer++ ) {

			for ( i = 0; i < cardsToDraw; i++ ) {
				// save game state before calling gainCard function
				memcpy(&pre, &game, sizeof(struct gameState)); 

				// randomly choose a card to gain by choosing number from 1 to 10
				temp = floor( Random() * 10 );	

				// execute gainCard function. note that k[temp] holds a card enum.
				// thi card enum coresponds to the supply position in the 
				// supplyCount array which holds supply counts.
				success = gainCard( k[temp], &game, flag, curPlayer); 
				if ( success == -1 ) {
#if (FAIL_RESULTS ==1)
					printf("GAIN CARD FAILED when gaining card for player %d at position %d. gainCard function returned -1.\n",
							curPlayer, k[temp]);
					printf("    Supply count of position %d is %d\n\n", k[temp], game.supplyCount[ k[temp] ]);
					printf("    Supply before the call: %d.\n\n", pre.supplyCount[ k[temp] ]);
#endif
				}
#if (ASSERTION_TESTS == 1)
				assert( success != - 1); 
#endif

				// check that handcount of currentPlayer was incremented and no other player
				// had there handcount incremented if flag set to 2.
				for ( j = 0; j < numPlayer; j++ ) {
					if ( j == curPlayer) {
						if ( (pre.handCount[curPlayer] +1 != game.handCount[curPlayer]) &&
								(flag == 2) ) {
#if (FAIL_RESULTS == 1)
							printf("GAIN CARD FAILED handcount test for curPlayer %d when deckCount at %d\n",
									curPlayer, pre.deckCount[curPlayer]);
							printf("    CurPlayer handcount: %d, Expected: %d\n\n",
									game.handCount[curPlayer], pre.handCount[curPlayer] + 1 );
#endif
						}
						else {
#if (PASS_RESULTS ==1)
							printf("GAIN CARD PASSED handcount test for curPlayer %d when deckCount at %d\n",
									curPlayer, pre.deckCount[curPlayer]);
						}
#endif
#if (ASSERTION_TESTS == 2)
						assert(pre.handCount[curPlayer] + 1 == game.handCount[curPlayer] );
#endif
					}
					else {
						if ( pre.handCount[j] != game.handCount[j] ) {
#if (FAIL_RESULTS == 1)
							printf("GAIN CARD FAILED handcount test for player %d when curPlayer %d gained card with %d flag set.\n", j, curPlayer, flag);
							printf("    Player %d handcount: %d, Expected: %d\n\n", j, game.handCount[j], pre.handCount[j]);
#endif
						}
						else {
#if (PASS_RESULTS == 1)
							printf("GAIN CARD PASSED handcount test for player %d when curPlayer %d gained card with %d flag set.\n", j, curPlayer, flag);
#endif
						}
#if (ASSERTION_TESTS == 1)
						assert(pre.handCount[j] == game.handCount[j] );
#endif
					}
				}

				// check that deckcount for current player is incremented when flag set to 1.
				// Make sure deckcount of current player not incremented when flag != 1.
				// Make sure deckcount doesn't change for any other players other than current.
				for ( j = 0; j < numPlayer; j++ ) {
					if ( j == curPlayer) {
						if ( ( pre.deckCount[curPlayer] + 1 != game.deckCount[curPlayer] ) &&
								(flag == 1) ) {
#if (FAIL_RESULTS == 1)
							printf("GAIN CARD FAILED deck test for curPlayer %d and when flag set to %d\n",
									curPlayer, flag);
							printf("    CurPlayer deckcount: %d, Expected: %d\n\n",
									game.deckCount[curPlayer], pre.deckCount[curPlayer] + 1 );
#endif
						}
						else {
#if (PASS_RESULTS == 1)
							printf("GAIN CARD PASSED deck test for curPlayer %d and when flag set to %d\n",
									curPlayer, flag);
#endif
						}
#if (ASSERTION_TESTS == 2)
						assert(pre.deckCount[curPlayer] + 1 == game.deckCount[curPlayer] );
#endif
					}
					else {
						if ( pre.deckCount[j] != game.deckCount[j] ) {
#if (FAIL_RESULTS == 1)
							printf("GAIN CARD PASSED deck test for player %d when curPlayer %d gained card with flag set to %d.\n",
									j, curPlayer, flag);
							printf("    Deck count: %d, Expected: %d\n\n", game.deckCount[j], pre.deckCount[j]);
#endif
						}
						else {
#if (PASS_RESULTS ==1)
							printf("GAIN CARD PASSED deck test for player %d when curPlayer %d gained card with flag set to %d.\n",
									j, curPlayer, flag);
#endif

						}
#if (ASSERTION_TESTS == 1)
						assert( pre.deckCount[j] == game.deckCount[j] );
#endif
					}
				}


				// check that discard count for current player is incremented when flag set to 0.
				// Make sure discard count of current player not incremented when flag != 0.
				// Make sure discard count doesn't change for any other players other than current.
				for ( j = 0; j < numPlayer; j++ ) {
					if ( j == curPlayer) {
						if ( ( pre.discardCount[curPlayer] + 1 != game.discardCount[curPlayer] ) &&
								(flag == 0) ) {
#if (FAIL_RESULTS == 1)
							printf("GAIN FAILED discard test for curPlayer %d and when flag set to %d\n",
									curPlayer, flag);
							printf("    CurPlayer discard count: %d, Expected: %d\n\n",
									game.discardCount[curPlayer], pre.discardCount[curPlayer] + 1 );
#endif
						}
						else {
#if (PASS_RESULTS)
							printf("GAIN CARD PASSED discard test for curPlayer %d and when flag set to %d\n",
									curPlayer, flag);

#endif
						}
#if (ASSERTION_TESTS == 2)
						assert(pre.discardCount[curPlayer] + 1 == game.discardCount[curPlayer] );
#endif
					}
					else {
						if ( pre.discardCount[j] != game.discardCount[j] ) {
#if (FAIL_RESULTS == 1)
							printf("GAIN CARD FAILED discard test for player %d when curPlayer %d gained card with flag set to %d.\n",
									j, curPlayer, flag);
							printf("    Discard count: %d, Expected: %d\n\n", game.discardCount[j], pre.discardCount[j]);
#endif
						}
						else {
							printf("GAIN CARD PASSED discard test for player %d when curPlayer %d gained card with flag set to %d.\n",
									j, curPlayer, flag);

						}
#if (ASSERTION_TESTS == 1)
						assert( pre.discardCount[j] == game.discardCount[j] );
#endif
					}
				}


				// check that supplyCount of card gained was decremented
				if ( pre.supplyCount[ k[temp] ] - 1  != game.supplyCount[ k[temp] ] ) {
#if (FAIL_RESULTS == 1)
					printf("GAIN CARD FAILED supply count test. Cards: %d, Expected: %d\n\n",
							pre.supplyCount[ k[temp] ], game.supplyCount[ k[temp] ] );
#endif
				}
#if (PASS_RESULTS  == 1)
				else {
					printf("GAIN CARD PASSED supply count test. Cards: %d, Expected: %d\n\n",
							pre.supplyCount[ k[temp] ], game.supplyCount[ k[temp] ] );
				}
#endif
#if (ASSERTION_TESTS == 1)
				assert( pre.supplyCount[ k[temp] ] - 1 == game.supplyCount[ k[temp] ] );
#endif
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// CHECK BOUNDARY CASE WHERE SUPPLY COUNT IS ZERO. MAKE SURE THAT GAIN CARD
	// RETURNS -1 AS EXPECTED AND DOES NOT GIVE A CARD TO ANY PLAYER
	///////////////////////////////////////////////////////////////////////////////

	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
		printf("Initialization of test failed.\n");
		return -1;
	} 

	// set up the supply counts of each card to 0
	for ( i = 0; i < 10; i++ ) {
		game.supplyCount[ k[i] ] = 0;
	} 


	// set up a loop to test gainCard for each separate flag:
	// Flag set to 0: should add card to discard pile
	// set to 1: should add to deck
	// set to 2: should add to hand
	for ( flag = 0; flag < 3; flag++ ) {
		// test function for different players
		for ( curPlayer = 0; curPlayer < numPlayer; curPlayer++ ) {

			for ( i = 0; i < cardsToDraw; i++ ) {
				// save game state before calling gainCard function
				memcpy(&pre, &game, sizeof(struct gameState)); 

				// randomly choose a card to gain by choosing number from 1 to 10
				temp = floor( Random() * 10 );	

				// execute gaincard function and make sure that it returns -1 as it should
				// because the supply counts of all possible card choices is zero.
				success = gainCard( k[temp], &game, flag, curPlayer); 
				if ( success != -1 ) {
#if (FAIL_RESULTS ==1)
					printf("GAIN CARD FAILED when gaining card for player %d at position %d. gainCard function did not return -1 when supply 0.\n\n",
							curPlayer, k[temp]);
#endif
#if (ASSERTION_TESTS == 1)
					assert( success == - 1 ); 
#endif
				}

				// make sure hand count was NOT incremented 
				// or changed for any player because supply count is set to 0
				for ( j = 0; j < numPlayer; j++ ) {
					if ( pre.handCount[curPlayer] != game.handCount[curPlayer] ) {
#if (FAIL_RESULTS == 1)
						printf("GAIN CARD FAILED hand count test when supply count set to 0, card %d drawn and flag set to %d.\n ",
								k[temp], flag);
						printf("    Hand count of player %d changed to: %d. Expected: %d\n\n",
								j, game.handCount[curPlayer], pre.handCount[curPlayer] );
#endif
#if (PASS_RESULTS ==1)
						printf("GAIN CARD PASSED hand count test when supply count set to 0, card %d drawn and flag set to %d.\n",
								k[temp], flag);
#endif
#if (ASSERTION_TESTS == 1)
						assert( pre.handCount[curPlayer] == game.handCount[curPlayer] );
#endif
					}
				}

				// make sure deck count was NOT incremented or changed for any
				// player because supply count is set to 0
				for ( j = 0; j < numPlayer; j++ ) {
#if (FAIL_RESULTS == 1)
					if ( pre.deckCount[curPlayer] != game.deckCount[curPlayer] ) {
						printf("GAIN CARD FAILED deck count test when supply zero and card %d drawn and flag set to %d.\n\n",
								k[temp], flag );
#endif
					}
					else {
#if (PASS_RESULTS == 1)
						printf("GAIN CARD PASSED deck count test when supply zero and card %d drawn and flag set to %d.\n\n",
								k[temp], flag );
#endif
					}
#if (ASSERTION_TESTS == 1)
					assert( pre.deckCount[curPlayer] == game.deckCount[curPlayer] );	    }
#endif
			}

			// make sure discard count was NOT incremented or changed for 
			// any player because supply count is set to 0.
			for ( j = 0; j < numPlayer; j++ ) {
#if (FAIL_RESULTS == 1)
				if ( j == curPlayer ) {
					if ( pre.discardCount[curPlayer] != game.discardCount[curPlayer] ) {
						printf("GAIN CARD FAILED discard count test for curPlayer when card %d drawn with supply of 0 and flag is %d.\n",
								k[temp], flag );
						printf("    Discard count: %d Expected: %d\n\n", pre.discardCount[curPlayer], game.discardCount[curPlayer] );
#endif
					}
					else {
						printf("GAIN CARD PASSED discard count test for curPlayer when card %d drawn with supply of 0 and flag is %d.\n",
								k[temp], flag );
					}
#if (ASSERTION_TESTS == 1)
					assert( pre.discardCount[curPlayer] == game.discardCount[curPlayer] );
#endif
				}
				else {
					if (pre.discardCount[j] != game.discardCount[j] ) {
#if (FAIL_RESULTS == 1)
						printf("GAIN CARD FAILED discard count test for player %d when curPlayer drew card %d with zero supply and flag is %d.\n",
								j, k[temp], flag );
						printf("Discard count: %d, Expected: %d\n\n", game.discardCount[j], pre.discardCount[j] );
#endif
					}
					else {
#if (PASS_RESULTS == 1)
						printf("GAIN CARD PASSED discard count test for player %d when curPlayer drew card %d with zero supply and flag is %d.\n",
								j, k[temp], flag );
#endif
					}
#if (ASSERTION_TESTS == 1)
					assert( game.discardCount[j] == pre.discardCount[j] );
#endif
				}
			}	
		}
	}

	return 0;
}
