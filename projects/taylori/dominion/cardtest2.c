//  Ian Taylor
//  CS 362 - Assignment 3
//  cardtest1.c: villageCard() test
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
    
    printf ("TESTING villageCard():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    state.hand[whoseTurn(&state)][0] = village; // player has village card in hand
    numCards = state.handCount[whoseTurn(&state)]; // get the current number of cards in player's hand
    numActions = state.numActions; // get the current number of actions
    
    // PLAYER 1 TESTS
    // Print hand before test
    printf("\nPreconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    
    // Call the Village Card
    villageCard(&state, whoseTurn(&state), 0);
    
    printf("\nPostconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    // Player should have 0 more cards in their hand, because they discard the village card and gaine one card.
    if(state.handCount[whoseTurn(&state)] == numCards) {
        printf("villageCard() handCount test PASSED:\n");
    }
    else {
        printf("villageCard() handCount test FAILED: incorrect number of cards in player's hand.\n");
    }
    
    // Player should have 2 more cards in their available, because they gain 2 from village card
    if(state.numActions == numActions + 2) {
        printf("villageCard() numActions test PASSED:\n");
    }
    else {
        printf("villageCard() numActions test FAILED: incorrect number of actions available to the player.\n");
    }
    
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    endTurn(&state); // end current player's turn
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    
    // PLAYER 2 TESTS
    // Print hand before test
    printf("\nPreconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    
    // Call the Village Card
    villageCard(&state, whoseTurn(&state), 1);
    
    printf("\nPostconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    printf("\tNumber of Actions: %d\n", state.numActions);
    
    
    // Player should have 0 more cards in their hand, because they discard the village card and gaine one card.
    if(state.handCount[whoseTurn(&state)] == numCards) {
        printf("villageCard() handCount test PASSED:\n");
    }
    else {
        printf("villageCard() handCount test FAILED: incorrect number of cards in player's hand.\n");
    }
    
    // Player should have 2 more cards in their available, because they gain 2 from village card
    if(state.numActions == numActions + 2) {
        printf("villageCard() numActions test PASSED:\n");
    }
    else {
        printf("villageCard() numActions test FAILED: incorrect number of actions available to the player.\n");
    }
    
    
    return 0;
}


