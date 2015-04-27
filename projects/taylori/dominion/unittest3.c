//  Ian Taylor
//  CS 362 - Assignment 3
//  unittest3.c:   isGameOver() test
//
//




#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>


int main(){
    
    
    int i, r;
    int seed = 1000;
    int numPlayer = 2;
    int handCount, deckCount, discardCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    printf ("TESTING isGameOver():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    

    // TESTS that game does not register as over when it begins
    printf("\nPre-test:\n");
    printf("\tProvince Count: %d\n", state.supplyCount[province]);
    if(!isGameOver(&state)){
        printf("PASSED. Game is not yet over.\n");
    }
    else{
        printf("FAIL. Game registers as completed.\n");
    }
    
    
    // TEST that isGameOver() returns true when province supply empty
    state.supplyCount[province] = 0;
    
    printf("\nPost:\n");
    printf("\tProvince Count: %d\n", state.supplyCount[province]);
    if(isGameOver(&state)){
        printf("PASSED. Game is over.\n");
    }
    else{
        printf("FAIL. Game does not register as over.\n");
    }
    
    
    // reset for tests of other card supplies:
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game

    
    state.supplyCount[gardens] = 0;
    state.supplyCount[duchy] = 0;
    state.supplyCount[smithy] = 0;
    
    printf("Non-Province Supply Test:\n");
    if(isGameOver(&state)){
        printf("PASSED. Game is over.\n");
    }
    else{
        printf("FAIL. Game does not register as over.\n");
    }
    
    return 0;
}


