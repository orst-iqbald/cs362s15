//  Ian Taylor
//  CS 362 - Assignment 3
//  unittest1.c: updateCoins() test
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
    
    srand(time(NULL)); // random used to randomly generate treasure cards
    
    int i, r;
    int seed = 1000;
    int numPlayer = 2;
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    printf ("TESTING updateCoins():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    

    // PLAYER 1 TESTS
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){
        state.hand[whoseTurn(&state)][i] = estate; // ensure no treasure cards
    }
    
    
    // initial call to updateCoins should register as 0
    updateCoins(whoseTurn(&state), &state, 0);
    
    // variables to track number of different treasure cards
    int numCoins = 0;
    
    
    // Print hand before test
    printf("\Initial:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    if(state.coins == numCoins){
        printf("\tPASS: Coins Amount: %d\n", state.coins);
    }
    else{
        printf("\tFAIL: Expected Coins: %d \tRecorded Coins: %d\n"
               , numCoins, state.coins);
    }

    
    // randomly assign treasure cards to hand
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){
        switch (rand() % 3) {
            case 0:
                state.hand[whoseTurn(&state)][i] = copper;
                numCoins += 1;
                break;
            case 1:
                state.hand[whoseTurn(&state)][i] = silver;
                numCoins += 2;
                break;
            case 2:
                state.hand[whoseTurn(&state)][i] = gold;
                numCoins += 3;
                break;
            default:
                break;
        }
    }
    
    // should update coins to equivalent of numCoins
    updateCoins(whoseTurn(&state), &state, 0);
    
    // Print hand before test
    printf("\Post:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    if(state.coins == numCoins){
        printf("\tPASS: Coins Amount: %d\n", state.coins);
    }
    else{
        printf("\tFAIL: Expected Coins: %d \tRecorded Coins: %d\n"
               , numCoins, state.coins);
    }
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    endTurn(&state); // end current player's turn
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    // PLAYER 2 TESTS
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){
        state.hand[whoseTurn(&state)][i] = estate; // ensure no treasure cards
    }
    
    
    // initial call to updateCoins should register as 0
    updateCoins(whoseTurn(&state), &state, 0);
    
    // variables to track number of different treasure cards
    numCoins = 0;
    
    
    // Print hand before test
    printf("\Initial:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    if(state.coins == numCoins){
        printf("\tPASS: Coins Amount: %d\n", state.coins);
    }
    else{
        printf("\tFAIL: Expected Coins: %d \tRecorded Coins: %d\n"
               , numCoins, state.coins);
    }
    
    
    // randomly assign treasure cards to hand
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){
        switch (rand() % 3) {
            case 0:
                state.hand[whoseTurn(&state)][i] = copper;
                numCoins += 1;
                break;
            case 1:
                state.hand[whoseTurn(&state)][i] = silver;
                numCoins += 2;
                break;
            case 2:
                state.hand[whoseTurn(&state)][i] = gold;
                numCoins += 3;
                break;
            default:
                break;
        }
    }
    
    // should update coins to equivalent of numCoins
    updateCoins(whoseTurn(&state), &state, 0);
    
    // Print hand before test
    printf("\Post:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    if(state.coins == numCoins){
        printf("\tPASS: Coins Amount: %d\n", state.coins);
    }
    else{
        printf("\tFAIL: Expected Coins: %d \tRecorded Coins: %d\n"
               , numCoins, state.coins);
    }

    
    
        return 0;
}


