#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

#define TESTFUNC "fullDeckCount()"

int main() {
    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	char* cardName[] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse", "sea_hag", "tribute", "smithy", "council_room"};
	int numCardTypes = 10, minCards = 0, maxCards = 12;

	//set up game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// 100% target cards in hand
	printf("Asserting hand contains only target card type.\n");
	for (i=minCards; i<=maxCards; i+=4) {
		G.handCount[thisPlayer] = i;

		printf("Testing cards for count of %d\n", i);

		for (j=0; j<numCardTypes; j++) {
			for (m=0; m<i; m++) {
				G.hand[thisPlayer][m] = k[j];	// assigns target card type
			}
			printf("total cards = %d, %12s = %d, expected = %d\n",
					i, cardName[j], fullDeckCount(thisPlayer, k[j], &G), i);
			assert(fullDeckCount(thisPlayer, k[j], &G) == i);
		}
	}

	// 0% target cards in hand
	printf("Asserting hand contains only dummy cards.\n");
	for (i=minCards; i<=maxCards; i+=4) {
		G.handCount[thisPlayer] = i;

		printf("Testing cards for count of %d\n", i);
		for (j=0; j<numCardTypes; j++) {
			for (m=0; m<i; m++) {
				G.hand[thisPlayer][m] = copper;	// assigns dummy card type
			}
			printf("total cards = %d, %12s = %d, expected = %d\n",
					i, cardName[j], fullDeckCount(thisPlayer, k[j], &G), 0);
			assert(fullDeckCount(thisPlayer, k[j], &G) == 0);
		}
	}

	printf("All tests passed.\n");

    return 0;
}
