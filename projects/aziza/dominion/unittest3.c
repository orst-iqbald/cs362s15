/* -----------------------------------------------------------------------
 * Testing the getCost() function in dominion.
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int failed = 0;

    int costArray[27] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    const char *nameArray[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

    //Taken from the example:
    printf ("TESTING getCost():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    for(int i = 0; i < 27; i++) {
    	if(getCost(i) == costArray[i]) {
    		printf("Testing \"%s\" card...PASSED\n", nameArray[i]);
    	}
    	else {
    		printf("Testing \"%s\" card...FAILED\n", nameArray[i]);
    		failed++;
    	}
    }

    if(failed == 0) {
    	printf("\nAll Tests Passed\n");
    }
    else {
    	printf("\nNot All Tests Passed\n");
    }



	return 0;
}