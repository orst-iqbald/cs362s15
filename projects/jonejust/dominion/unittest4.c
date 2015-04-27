///////////////////////////////////////////////////////////////////////////////
// UNIT TEST#4 - buyCard FUNCTION
///////////////////////////////////////////////////////////////////////////////
// Include the following lines in the makefile
//
// unittest4: unittest4.c dominion.c rngs.c
// 	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)
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


// Test for checking that buyCard handles checking the cost of cards
// properly and making sure the right coins are deducted or 
// whether the buying of card can be afforded at all.
void costCoinsTest(int supplyPos, int coins, struct gameState *game, int k[10] ) {

	int success;
	game->coins = coins;

	// ensure numBuys is > 1 so buyCard doesn't fail for tht reason.
	game->numBuys = 10;

	// attempt to buy the random card with the random
	// number of coins
	success = buyCard( k[supplyPos], game);

	// now check to make sure buyCard function handled
	// checking the price and allowing the player to 
	// buy or not correctly.
	if ( getCost(k[supplyPos]) > coins ) {

		if ( success != -1 ) {
#if (FAIL_RESULTS == 1)
			printf("BUY CARD FAILED cost test. Didn't return -1 for card %d when cost %d and coins %d\n\n",
					k[supplyPos], getCost( k[supplyPos] ), coins ); 
#endif
		}
		else {
#if (PASS_RESULTS ==1)
			printf("BUY CARD PASSED cost test. Returned -1 for card %d when cost %d and coins %d\n\n",
					k[supplyPos], getCost( k[supplyPos] ), coins ); 
#endif
		}
#if (ASSERTION_TESTS == 1)
		assert( success == -1);
#endif
	}
	else {
		if ( ((coins - getCost(k[supplyPos])) != game->coins) &&
				(success != -1)  ) {
#if (FAIL_RESULTS ==1)
			printf("BUY CARD FAILED to subtract cost of card from coins.\n");
			printf("    Card cost: %d, Coins before: %d, Coins after: %d\n\n",
					getCost(k[supplyPos]), coins, game->coins );
#endif
		}
		else {
			printf("BUY CARD PASSED in subtracting cost of card from coins.\n");
			printf("    Card cost: %d, Coins before: %d, Coins after: %d\n\n",
					getCost(k[supplyPos]), coins, game->coins );
		}
#if (ASSERTION_TESTS ==1)
		assert( (coins - getCost( k[supplyPos])) == game->coins );
#endif
	}
}


// Test function for testing the number of buys
void buyCardTest(int supplyPos, int coins, struct gameState *game, int k[10], int numBuys) {

	int success;

	// set up conditions to test under
	game->coins = coins;
	game->numBuys = numBuys;

	// run the buy card function on cardNumber
	success = buyCard(supplyPos, game);

	if (success != -1) {

		if ( (numBuys -1 != game->numBuys ) || ( numBuys <= 0 ) ) {
#if (FAIL_RESULTS ==1)
			printf("BUY CARD FAILED to decrement numBuys on successful buy. Game->numBuys: %d, Expected: %d\n\n",
					game->numBuys, numBuys - 1);
#endif
		}
		else {
#if (PASS_RESULTS ==1)
			printf("BUY CARD PASSED in decrementing numBuys on successful buy.\n");
#endif
		}
#if (ASSERTION_TESTS ==1)
		assert( numBuys - 1 == game->numBuys );
#endif
	}
	else {
		if ( numBuys != game->numBuys ) {
#if (FAIL_RESULTS ==1)
			printf("BUY CARD FAILED to keep numBuys the same when failing to buy. game->numBuys: %d, Expected: %d\n\n",
					game->numBuys, numBuys);
#endif
		}
#if (PASS_RESULTS ==1)
		printf("BUY CARD PASSED in keeping numBuys the same when failing to buy.\n");
#endif
#if (ASSERTION_TESTS ==1)
		assert( game->numBuys == numBuys);
#endif
	}

}


int main() {


	int i, j, success;
	int temp, temp2;
	int curPlayer;
	int initialDiscardCount = 0; // starting here to test boundary of zero for buyCard
	int initialDeckCount = 0; // starting the buy card here to test boundary of zero
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
		game.supplyCount[ k[i] ] = cardsToDraw * numPlayer;
	}

	// test buyCard function for different players
	for ( curPlayer = 0; curPlayer < numPlayer; curPlayer++ ) {
		game.whoseTurn = curPlayer;
		for ( i = 0; i < cardsToDraw; i++ ) {
			// because only testing card counts here, set game->coins
			// to 100 so buyCard doesn't fail for reasons of money
			// yet. same for num->Buys. We will test this functionality later
			game.coins = 100;
			game.numBuys = 10;

			// save game state before calling buyCard function
			memcpy(&pre, &game, sizeof(struct gameState)); 

			// randomly choose a card to buy by choosing number from 1 to 10
			temp = floor( Random() * 10 );	

			// execute buyCard function. note that k[temp] holds a card enum.
			// this card enum coresponds to the supply position in the 
			// supplyCount array which holds supply counts.
			success = buyCard( k[temp], &game);
			// check if buyCard failed. It shouldn't fail yet because 
			// we have 100 in coins and supply count is:
			// numPlayers * cardsInDrawTest 
			if ( success == -1 ) {
#if (FAIL_RESULTS ==1)
				printf("BUY CARD FAILED when buying card for player %d at position %d. buyCard function returned -1.\n",
						curPlayer, k[temp]);
				printf("    Supply count of position %d is %d. Coins are %d.\n", k[temp], game.supplyCount[ k[temp] ], game.coins);
				printf("    Supply before the call: %d.\n\n", pre.supplyCount[ k[temp] ]);
#endif
#if (ASSERTION_TESTS == 1)
				assert( success != - 1); 
#endif
			}

			// check that handcount of currentPlayer was NOT incremented and no other player
			// had there handcount incremented. Card should be going in discard pile of
			// current player
			for ( j = 0; j < numPlayer; j++ ) {
				if ( j == curPlayer) {
					if ( pre.handCount[curPlayer] != game.handCount[curPlayer] ) {
#if (FAIL_RESULTS == 1)
						printf("BUY CARD FAILED handcount test for curPlayer %d.\n",
								curPlayer );
						printf("    CurPlayer handcount: %d, Expected: %d\n\n",
								game.handCount[curPlayer], pre.handCount[curPlayer] + 1 );
#endif
					}
					else {
#if (PASS_RESULTS ==1)
						printf("BUY CARD PASSED handcount test for curPlayer %d.\n",
								curPlayer );
#endif
					}
#if (ASSERTION_TESTS == 1)
					assert(pre.handCount[curPlayer] == game.handCount[curPlayer] );
#endif
				}
				else {
					if ( pre.handCount[j] != game.handCount[j] ) {
#if (FAIL_RESULTS == 1)
						printf("BUY CARD FAILED handcount test for player %d when curPlayer %d bought card.\n", j, curPlayer);
						printf("    Player %d handcount: %d, Expected: %d\n\n", j, game.handCount[j], pre.handCount[j]);
#endif
					}
					else {
#if (PASS_RESULTS ==1)
						printf("BUY CARD passed handcount test for player %d when curPlayer %d bought card.\n", j, curPlayer);
#endif
					}
#if (ASSERTION_TESTS == 1)
					assert(pre.handCount[j] == game.handCount[j] );
#endif
				}
			}
		}

		// check that deckcount NOT incremented for any player. bought cards should
		// be going to the discard pile.
		for ( j = 0; j < numPlayer; j++ ) {
			if ( j == curPlayer) {
				if ( pre.deckCount[curPlayer] != game.deckCount[curPlayer] ) {
#if (FAIL_RESULTS == 1)
					printf("BUY CARD FAILED deck test for curPlayer %d when card %d bought.\n",
							curPlayer, k[temp] );
					printf("    CurPlayer deck count: %d, Expected: %d\n\n",
							game.deckCount[curPlayer], pre.deckCount[curPlayer] );
#endif
				}
				else {
#if (PASS_RESULTS ==1)
					printf("BUY CARD PASSED deck test for curPlayer %d when card %d bought.\n",
							curPlayer, k[temp] );
#endif
				}
#if (ASSERTION_TESTS == 1)
				assert(pre.deckCount[curPlayer] == game.deckCount[curPlayer] );
#endif
			}
			else {
				if ( pre.deckCount[j] != game.deckCount[j] ) {
#if (FAIL_RESULTS == 1)
					printf("BUY CARD FAILED deck test for player %d when curPlayer %d bought card %d.\n",
							j, curPlayer, k[temp] );
					printf("    Deck count: %d, Expected: %d\n\n", game.deckCount[j], pre.deckCount[j]);
#endif
				}
				else {
#if (PASS_RESULTS ==1)
					printf("BUY CARD PASSED deck test for player %d when curPlayer %d bought card %d.\n",
							j, curPlayer, k[temp] );
#endif
				}
#if (ASSERTION_TESTS == 1)
				assert( pre.deckCount[j] == game.deckCount[j] );
#endif
			}
		}


		// check that discard count for current player is incremented for current player
		// and no other player's discard piles are incremented.
		for ( j = 0; j < numPlayer; j++ ) {
			if ( j == curPlayer) {
				if ( pre.discardCount[curPlayer] + 1 != game.discardCount[curPlayer] ) {
#if (FAIL_RESULTS == 1)
					printf("BUY CARD FAILED discard test for curPlayer %d, discardcount: %d, Expected: %d\n\n",
							curPlayer, game.discardCount[curPlayer], pre.discardCount[curPlayer] + 1 );
#endif
				}
				else {
#if (PASS_RESULTS ==1)
					printf("BUY CARD PASSED in incrementing discard pile for curPlayer %d.\n\n",
							curPlayer );
#endif
				}
#if (ASSERTION_TESTS == 1)
				assert(pre.discardCount[curPlayer] + 1 == game.discardCount[curPlayer] );
#endif
			}
			else {
				if ( pre.discardCount[j] != game.discardCount[j] ) {
#if (FAIL_RESULTS == 1)
					printf("BUY CARD FAILED discard test for other player %d when curPlayer %d bought card.\n",
							j, curPlayer);
					printf("    Discard count: %d, Expected: %d\n\n", game.discardCount[j], pre.discardCount[j]);
#endif
				}
				else {
#if (PASS_RESULTS ==1)
					printf("BUY CARD PASSED in not incrementing count for other player %d when curPlayer %d bought card.\n",
							j, curPlayer);
#endif
				}
#if (ASSERTION_TESTS == 1)
				assert( pre.discardCount[j] == game.discardCount[j] );
#endif
			}
		}
	}


	// check that supplyCount of card bought was decremented
	if ( pre.supplyCount[ k[temp] ] - 1  != game.supplyCount[ k[temp] ] ) {
#if (FAIL_RESULTS == 1)
		printf("BUY CARD FAILED supply count test. Cards: %d, Expected: %d\n\n",
				game.supplyCount[ k[temp] ], pre.supplyCount[ k[temp] ] - 1  );
#endif
#if (ASSERTION_TESTS == 1)
		assert( pre.supplyCount[ k[temp] ] - 1 == game.supplyCount[ k[temp] ] );
#endif
	}
	else {
#if (PASS_RESULTS ==1)
		printf("BUY CARD PASSED in decrementing supply count.\n");
#endif
	}


	///////////////////////////////////////////////////////////////////////////////
	// CHECK BOUNDARY CASE WHERE SUPPLY COUNT IS ZERO. MAKE SURE THAT BUY CARD
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

	// test function for different players
	for ( curPlayer = 0; curPlayer < numPlayer; curPlayer++ ) {

		for ( i = 0; i < cardsToDraw; i++ ) {
			// set coins to 100 so buyCard doesn't fail for lack of money
			// this section is just to test to see if cards are bought
			// when there aren't supposed to be any in the supply
			game.coins = 100;

			// save game state before calling buyCard function
			memcpy(&pre, &game, sizeof(struct gameState)); 

			// randomly choose a card to buy by choosing number from 1 to 10
			temp = floor( Random() * 10 );	

			// execute buy card function and make sure that it returns -1 as it should
			// because the supply counts of all possible card choices is zero.
			success = buyCard( k[temp], &game ); 
			if ( success != -1 ) {
#if (FAIL_RESULTS ==1)
				printf("FAILED when buying card of zero supply at position %d. buyCard function did not return -1\n\n",
						k[temp]);
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
					printf("FAILED hand count test when card %d drawn with supply count set to 0.", k[temp] );
					printf("Hand count of player %d changed to: %d. Expected: %d\n\n",
							j, game.handCount[curPlayer], pre.handCount[curPlayer] );
#endif
#if (ASSERTION_TESTS == 1)
					assert( pre.handCount[curPlayer] != game.handCount[curPlayer] );
#endif
				}
			}

			// make sure deck count was NOT incremented or changed for any
			// player because supply count is set to 0
			for ( j = 0; j < numPlayer; j++ ) {
#if (FAIL_RESULTS == 1)
				if ( pre.deckCount[j] != game.deckCount[j] ) {
					printf("FAILED deck count test for player %d when curPlayer %d drew with supply count zero. ",
							j, curPlayer);
					printf("Deck count: %d, Expected: %d\n\n", game.deckCount[curPlayer], pre.deckCount[curPlayer] );
#endif
#if (ASSERTION_TESTS == 1)
					assert( pre.handCount[curPlayer] != game.handCount[curPlayer] );
#endif
				}
			}

			// make sure discard count was NOT incremented or changed for 
			// any player because supply count is set to 0.
			for ( j = 0; j < numPlayer; j++ ) {
#if (FAIL_RESULTS == 1)
				if ( pre.discardCount[j] != game.discardCount[j] ) {
					printf("FAILED discard count test for player %d when curPlayer %d drew from zero supply count.\n\n",
							j, curPlayer );
#endif
#if (ASSERTION_TESTS == 1)
					assert( pre.discardCount[curPlayer] != game.discardCount[curPlayer] );
#endif
				}
			}	
		}
	}


	///////////////////////////////////////////////////////////////////////////////
	// TEST THE UPDATING COINS WITH BUY CARD FUNCTION & MAKING SURE NOT 
	// BUYING CARDS THAT COST TOO MUCH
	///////////////////////////////////////////////////////////////////////////////


	for ( i = 0; i < 50; i++ ) {

		// reinitialize each time to make sure things aren't in a weird state
		success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
		if (success == -1) {
			printf("Initialization of test failed.\n");
			return -1;
		}

		// run a hundred random tests to check if checking coins is
		// properly done and checking whether a card can be afforded.
		temp = rand() % 10;
		temp2 = rand() % 10;
		costCoinsTest(temp, temp2, &game, k);

	}

	// check a couple of boundary conditions
	// reinitialize each time to make sure things aren't in a weird state
	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
		printf("Initialization of test failed.\n");
		return -1;
	}
	temp = silver;
	temp2 = -1;
	costCoinsTest(temp, temp2, &game, k);

	// reinitialize each time to make sure things aren't in a weird state
	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
		printf("Initialization of test failed.\n");
		return -1;
	}
	temp = province;
	temp2 = -9;
	costCoinsTest(temp, temp2, &game, k);

	// reinitialize each time to make sure things aren't in a weird state
	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
		printf("Initialization of test failed.\n");
		return -1;
	}
	temp = silver;
	temp2 = 2;
	costCoinsTest(temp, temp2, &game, k);

	///////////////////////////////////////////////////////////////////////////////
	// TEST THAT BUY CARD DECREMENTS NUMBER OF BUYS PROPERLY
	///////////////////////////////////////////////////////////////////////////////

	for ( i = 0; i < 50; i++ ) {

		// reinitialize each time to make sure things aren't in a weird state
		success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
		if (success == -1) {
			printf("Initialization of Buy Card test failed.\n");
			return -1;
		}

		// run a hundred random tests to check if checking coins is
		// properly done and checking whether a card can be afforded.
		temp = rand() % 10;
		temp2 = rand() % 10; // number of Buys to test with
		buyCardTest( k[temp], 100, &game, k, temp2);

	}

	// reinitialize each time to make sure things aren't in a weird state
	success = initializeDrawCardTest(numPlayer, k, seed, &game, initialDeckCount, initialDiscardCount);
	if (success == -1) {
		printf("Initialization of Buy Card test failed.\n");
		return -1;
	}
	temp = rand() % 10;
	buyCardTest( k[temp], 100, &game, k, -1 ); // see what happens if we have negative buys

	temp = rand() % 10;
	buyCardTest( k[temp], 100, &game, k, -5 ); // see what happens if we have negative buys

	temp = rand() % 10;
	buyCardTest( k[temp], 100, &game, k, 0 ); // see what happens if we have negative buys



	return 0;

}
