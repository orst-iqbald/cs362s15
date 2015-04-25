/* -----------------------------------------------------------------------
 * Test for getCost() function from dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define ALL_CARDS 27

int cardCosts[ALL_CARDS] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

const char *cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
    "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
    "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

int main() {
    int i, c;
    printf ("TESTING getCost():\n");
    //loop to go through all the cards in the game. Added the +1 to test an input int input.
    for (i = 0; i < ALL_CARDS + 1; ++i) {
#if (NOISY_TEST == 1)
        printf("Test cost of %s card.\n", cardNames[i]);
#endif
        c = getCost(i);
#if (NOISY_TEST == 1)
        //case that cost of card returned from function matches value in array
        if(c == cardCosts[i]) {
            printf("Test Passed!\n");
        }
        //case that cardNumber input to function is not in the list
        else if(c < 0) {
            printf("Test Passed: Card Not Found, function returned %d as expected.\n", c);
        }
        //case that card cost doesn't match 
        else {
            printf("Test Failed: Expected %d, cost returned was %d.\n", cardCosts[i], c);
        }
#endif
    }
    printf("Testing Complete!\n");

    return 0;
}