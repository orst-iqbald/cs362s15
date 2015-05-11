/*
 * unittest3.c
 *
 *  

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "fullDeckCount()"

#define SPECIAL_NOTE "*** SPECIAL NOTE *** 										\n\
	the function fullDeckCount(), as written, takes a card as input				\n\
 	and counts the number of instances of that card.  I am writing my unit test	\n\
 	assuming that is the purpose and specification of the function.				\n\
 	Separately, I noticed that a different function scoreFor() calls the		\n\
 	fullDeckCount() for a different purpose, i.e. counting the total cards for	\n\
 	a given player, and not just counting a particular card.					\n\
 	\n\
 	Either scoreFor() or fullDeckCount(), or both, would need to be debugged	\n\
 	in integration testing for the intended results.\n\n"


/* NOTE *** This code provides the count of all cards for a player ***

	int myDeckCount = 0;
	for (i=0; i<27; i++) {
		myDeckCount += fullDeckCount(thisPlayer, i, &G);
		printf("i %d deck count %d\n", i, myDeckCount);
	}

*/

int main() {
    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	char* cardName[] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse",
			"sea_hag", "tribute", "smithy", "council_room"};
	int numCardTypes = 10, minCards = 0, maxCards = 12;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing: %s ----------------\n", TESTFUNC);

	// 100% target card in hand
	for (i=minCards; i<=maxCards; i+=4) {
		G.handCount[thisPlayer] = i;

		printf("**********Testing cards for count of %d**********\n", i);

		for (j=0; j<numCardTypes; j++) {
			for (m=0; m<i; m++) {
				G.hand[thisPlayer][m] = k[j];	// assigns target card type
			}
			printf("total cards = %d, %12s = %d, expected = %d\n",
					i, cardName[j], fullDeckCount(thisPlayer, k[j], &G), i);
			assert(fullDeckCount(thisPlayer, k[j], &G) == i);
		}
	}

	// 50% target card in hand
	for (i=minCards; i<=maxCards; i+=4) {
		G.handCount[thisPlayer] = i;

		printf("**********Testing cards for count of %d**********\n", i);
		for (j=0; j<numCardTypes; j++) {
			for (m=0; m<i; m+=2) {
				G.hand[thisPlayer][m] = k[j];		// assigns target card type
				G.hand[thisPlayer][m+1] = copper;	// assigns dummy card type
			}
			printf("total cards = %d, %12s = %d, expected = %d\n",
					i, cardName[j], fullDeckCount(thisPlayer, k[j], &G), i/2);
			assert(fullDeckCount(thisPlayer, k[j], &G) == i/2);
		}
	}

	// 0% target card in hand
	for (i=minCards; i<=maxCards; i+=4) {
		G.handCount[thisPlayer] = i;

		printf("**********Testing cards for count of %d**********\n", i);
		for (j=0; j<numCardTypes; j++) {
			for (m=0; m<i; m++) {
				G.hand[thisPlayer][m] = copper;	// assigns dummy card type
			}
			printf("total cards = %d, %12s = %d, expected = %d\n",
					i, cardName[j], fullDeckCount(thisPlayer, k[j], &G), 0);
			assert(fullDeckCount(thisPlayer, k[j], &G) == 0);
		}
	}

    printf("\n >>>>> SUCCESS: Testing complete for %s <<<<<\n\n", TESTFUNC);
    printf(SPECIAL_NOTE);

    return 0;
}
