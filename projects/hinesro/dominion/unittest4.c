/********************************
*      Test for shuffle().      *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "interface.c"
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

int testShuffle(int p, struct gameState *testState);

int main () {
    int cardArray[10] = {
        treasure_map, 
        sea_hag, salvager, 
        cutpurse, great_hall, 
        great_hall, 
        minion, 
        estate, 
        duchy, 
        province
    };
    int i, game, randomSeed = 415789;
    struct gameState test;
    game = initializeGame(MAX_PLAYERS, cardArray, randomSeed, &test);
    assert (game == 0);
    printf("BEGIN SHUFFLE TEST\n");
    for(i = 0; i < MAX_PLAYERS; i++) {
        testShuffle(i, &test);
    }
    printf("END SHUFFLE TEST\n");

    return 0;
}

int testShuffle(int p, struct gameState *testState) {
    printf("Original: ");
    printDeck(p, testState);
    shuffle(p, testState);
    printf("Result: ");
    printDeck(p, testState);

    return 0;
}