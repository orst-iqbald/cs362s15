#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int *k;
    
    printf("Testing that kingdomCards() stores cards correctly.\n");

    k = kingdomCards(adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall);

    assert(k[0] == adventurer);
    assert(k[1] == council_room);
    assert(k[2] == feast);
    assert(k[3] == gardens);
    assert(k[4] == mine);
    assert(k[5] == remodel);
    assert(k[6] == smithy);
    assert(k[7] == village);
    assert(k[8] == baron);
    assert(k[9] == great_hall);

    printf("All tests passed!\n");

    return 0;
}
