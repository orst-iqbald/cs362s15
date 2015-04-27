//*************************************
//Testing to check the values associated with the cards
//*************************************
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TEST 1
#define CARDS 27

int cardCosts[CARDS] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

const char *cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
    "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
    "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

int main() {
    int i, c;
    printf ("Now testing getCost():\n");
    //loop to go through all the cards in the game. Added the +1 to test an input int input.
    for (i = 0; i < CARDS + 1; ++i) {
#if (TEST == 1)
        printf("Test cost of %s card.\n", cardNames[i]);
#endif
        c = getCost(i);
#if (TEST == 1)
        //case that cost of card returned from function matches value in array
        if(c == cardCosts[i]) {
            printf("Test Passed!\n");
        }
        //case that cardNumber input to function is not in the list
        else if(c < 0) {
            printf("Test Passed: \n", c);
        }
        //case that card cost doesn't match 
        else {
            printf("Test Failed: ", cardCosts[i], c);
        }
#endif
    }
    

    return 0;
}