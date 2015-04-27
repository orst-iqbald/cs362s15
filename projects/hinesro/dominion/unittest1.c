/************************
*    getCost()  test    *
************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_CARDS 27
#define OUTPUT_TEST_RESULTS 1

const char *cards[] = {
    "curse", 
    "estate", 
    "duchy", 
    "province", 
    "copper", 
    "silver", 
    "gold", 
    "adventurer", 
    "council_room",
    "feast", 
    "gardens", 
    "mine", 
    "remodel", 
    "smithy", 
    "village", 
    "baron", 
    "great_hall", 
    "minion", 
    "steward", 
    "tribute",
    "ambassador", 
    "cutpurse", 
    "embargo", 
    "outpost", 
    "salvager", 
    "sea_hag", 
    "treasure_map"
};
int cardCosts[NUM_CARDS] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

int main() {
    printf ("Beginning getCost test...\n");
    int cost, i;
    for (i = 0; i < NUM_CARDS + 1; ++i) {
        #if (OUTPUT_TEST_RESULTS == 1)
            printf("Testing cost of %s card...\n", cards[i]);
        #endif
        cost = getCost(i);
        #if (OUTPUT_TEST_RESULTS == 1)
            if(cost == cardCosts[i]) {
                printf("Cost is correct, test passed.\n");
            } else if(cost < 0) {
                printf("Card Not Found and function returned %d, test passed.\n", cost);
            } else {
                printf("Expected %d but cost was %d. Test FAILED.\n", cardCosts[i], cost);
            }
        #endif
    }
    return 0;
}