/********************************
*    Test for supplyCount().    *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

int main () {
    struct gameState testState;
    int randSeed = 128;

    int cards[10] = {
        estate, 
        duchy, 
        province, 
        copper, 
        silver, 
        gold, 
        outpost, 
        salvager, 
        sea_hag, 
        treasure_map
    };
    initializeGame(2, cards, randSeed, &testState);
    assert(testState.supplyCount[curse] == 10);
    printf ("Begin test supplyCount().\n");
    assert(supplyCount(0, &testState) == 10);
    printf ("supplyCount() passes all tests.\n");

    return 0;
}