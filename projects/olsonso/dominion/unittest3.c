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

// this test will first go and assign the correct values with each of the given cards. Once ran though
//they should output the correct values.

int cardCosts[CARDS] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

const char *cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
    "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
    "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};

int main() {
    int i;
    int cost;
    printf ("Now testing getCost():\n");


    //start loop through cards
    //should print out each card indiviually with their own value
    //should be 27
    for (i = 0; i < CARDS + 1; ++i) {
#if (TEST == 1)
        printf("the given cost of %s card /n", cardNames[i]);
#endif
        cost = getCost(i);
#if (TEST == 1)
        //checks to see if the values match up
        if(cost == cardCosts[i]) {
            printf("Test Passed\n");
        }
        else {
            printf("Test Failed: ", cardCosts[i], cost);
        }
#endif
    }
    

    return 0;
}