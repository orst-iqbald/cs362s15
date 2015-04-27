//  Ian Taylor
//  CS 362 - Assignment 3
//  cardtest1.c: great_hall() test
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1



int main(){
    
    int i, r, numCards, numActions;
    int seed = 1000;
    int numPlayer = 2;
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    printf ("TESTING great_hallCard():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    state.hand[whoseTurn(&state)][0] = great_hall; // player has great_hall card in hand
    numCards = state.handCount[whoseTurn(&state)]; // get the current number of cards in player's hand
    numActions = state.numActions; // get the current number of actions
    

    // PLAYER 1 TESTS
    // Print hand before test
    printf("\nPreconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    // Call the Great Hall Card
    great_hallCard(&state, whoseTurn(&state), 0);
    
    printf("\nPostconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    // HandCount Test Results:
    if(state.handCount[whoseTurn(&state)] == numCards) {
        printf("great_hall() handCount test PASSED.\n");
    }
    else {
        printf("great_hall() handCount test FAILED: incorrect number of cards in player's hand.\n");
    }
    
    // numActions Test Results:
    if(state.numActions == numActions + 1) {
        printf("great_hall() numActions test PASSED.\n");
    }
    else {
        printf("great_hall() numActions test FAILED: incorrect number of actions available to the player.\n");
    }
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    endTurn(&state); // end current player's turn
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    

    state.hand[whoseTurn(&state)][0] = great_hall; // player has great_hall card in hand
    numCards = state.handCount[whoseTurn(&state)]; // get the current number of cards in player's hand
    numActions = state.numActions; // get the current number of actions
    
    // PLAYER 2 TESTS
    // Print hand before test
    printf("\nPreconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    // Call the Great Hall Card
    great_hallCard(&state, whoseTurn(&state), 0);
    
    printf("\nPostconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    // HandCount Test Results:
    if(state.handCount[whoseTurn(&state)] == numCards) {
        printf("great_hall() handCount test PASSED.\n");
    }
    else {
        printf("great_hall() handCount test FAILED: incorrect number of cards in player's hand.\n");
    }
    
    // numActions Test Results:
    if(state.numActions == numActions + 1) {
        printf("great_hall() numActions test PASSED.\n");
    }
    else {
        printf("great_hall() numActions test FAILED: incorrect number of actions available to the player.\n");
    }



    return 0;
}