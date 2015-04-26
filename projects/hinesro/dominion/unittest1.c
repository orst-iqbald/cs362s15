/********************************
*    Tests for updateCoins().   *
********************************/

#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>

int main() {
    struct gameState* testState = malloc(sizeof(struct gameState));
    int extraCoins, p = 0;

    testState->handCount[p] = 3;
    testState->hand[p][0] = gold;
    testState->hand[p][1] = adventurer;
    testState->hand[p][2] = copper;
    extraCoins = 0;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == 4);

    testState->handCount[p] = 1;
    testState->hand[p][0] = silver;
    extraCoins = 0;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == 2);

    testState->handCount[p] = 2;
    testState->hand[p][0] = province;
    testState->hand[p][1] = adventurer;
    extraCoins = 0;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == 0);

    testState->handCount[p] = 0;
    extraCoins = 0;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == 0);
    
    testState->handCount[p] = 0;
    extraCoins = 3;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == extraCoins);
    
    testState->handCount[p] = 1;
    testState->hand[p][0] = adventurer;
    extraCoins = 0;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == 0);
    
    testState->handCount[p] = 1;
    testState->hand[p][0] = silver;
    extraCoins = 1;
    updateCoins(p, testState, extraCoins);
    assert(testState->coins == (2 + extraCoins));
    
    return 0;
}