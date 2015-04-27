//  Ian Taylor
//  CS 362 - Assignment 3
//  unittest4.c:   scoreFor() test
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
    
    
    int i, r, player;
    int seed = 1000;
    int numPlayer = 2;
    int handCount, deckCount, discardCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    printf ("TESTING scoreFor():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    player = whoseTurn(&state);

    // TESTS
    
    // initialize the handcount, discardCount, and deckCount to 0.
    state.handCount[player] = 0;
    state.discardCount[player] = 0;
    state.deckCount[player] = 0;
    
    
    printf("\nPreconditions:\n");
    printf("\tHand Count: %d\tDiscard Count: %d\tDeck Count: %d\n", state.handCount[player], state.discardCount[player], state.deckCount[player]);
    if(scoreFor(player, &state)){
        printf("FAILED: Expected score of 0.\n");
    }
    else{
        printf("PASSED: returns 0.\n");
    }
    
    // reset game
    // TEST initialized game score -- expect three b/c of 3 estate cards
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    player = whoseTurn(&state);
    printf("\nPreconditions:\n");
    printf("\tHand Count: %d\tDiscard Count: %d\tDeck Count: %d\n", state.handCount[player], state.discardCount[player], state.deckCount[player]);
    if(scoreFor(player, &state) == 3){
        printf("PASSED: Returned score of 3.\n");
    }
    else{
        printf("PASSED: Expected score of 3.\n");
    }

    //set up deck to test individual paths -- hand, deck, discard
    // TESTING HAND
    state.handCount[player] = 5;
    state.discardCount[player] = 0;
    state.deckCount[player] = 0;

    for(i = 0; i < state.handCount[player]; i++){
        state.hand[player][i] = estate;
    }
    for(i = 0; i < state.deckCount[player]; i++){
        state.deck[player][i] = smithy;
    }
    for(i = 0; i < state.discardCount[player]; i++){
        state.discard[player][i] = smithy;
    }
    printf("\nTesting Hand:\nPreconditions:\n");
    printf("\tHand Count: %d\tDiscard Count: %d\tDeck Count: %d\n", state.handCount[player], state.discardCount[player], state.deckCount[player]);
    printf("\tScore: %d\n", scoreFor(player, &state));
    if(scoreFor(player, &state) == 5){
        printf("PASSED: Returned score of 5.\n");
    }
    else{
        printf("PASSED: Expected score of 5.\n");
    }

    //set up deck to test individual paths -- hand, deck, discard
    // TESTING DECK
    state.handCount[player] = 0;
    state.discardCount[player] = 0;
    state.deckCount[player] = 5;

    for(i = 0; i < state.handCount[player]; i++){
        state.hand[player][i] = smithy;
    }
    for(i = 0; i < state.deckCount[player]; i++){
        state.deck[player][i] = estate;
    }
    for(i = 0; i < state.discardCount[player]; i++){
        state.discard[player][i] = smithy;
    }
    printf("\nTesting Deck:\nPreconditions:\n");
    printf("\tHand Count: %d\tDiscard Count: %d\tDeck Count: %d\n", state.handCount[player], state.discardCount[player], state.deckCount[player]);
    printf("\tScore: %d\n", scoreFor(player, &state));
    if(scoreFor(player, &state) == 5){
        printf("PASSED: Returned score of 5.\n");
    }
    else{
        printf("FAILED: Expected score of 5.\n");
    }

    //set up deck to test individual paths -- hand, deck, discard
    // TESTING DISCARD
    state.handCount[player] = 0; // set hand count to 0
    state.discardCount[player] = 5; // set a discardCount of five
    state.deckCount[player] = 0;
    
    for(i = 0; i < state.handCount[player]; i++){
        state.hand[player][i] = smithy;
    }
    for(i = 0; i < state.deckCount[player]; i++){
        state.deck[player][i] = smithy;
    }
    for(i = 0; i < state.discardCount[player]; i++){
        state.discard[player][i] = estate;
    }
    printf("\nTesting Discard:\nPreconditions:\n");
    printf("\tHand Count: %d\tDiscard Count: %d\tDeck Count: %d\n", state.handCount[player], state.discardCount[player], state.deckCount[player]);
    printf("\tScore: %d\n", scoreFor(player, &state));
    if(scoreFor(player, &state) == 5){
        printf("PASSED: Returned score of 5.\n");
    }
    else{
        printf("FAILED: Expected score of 5.\n");
    }


    
    return 0;
}


