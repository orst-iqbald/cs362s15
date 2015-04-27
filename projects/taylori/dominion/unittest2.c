//  Ian Taylor
//  CS 362 - Assignment 3
//  unittest2.c:  drawCard() test
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
    
    printf ("TESTING drawCard():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    

    // TESTS
    int player = whoseTurn(&state);
    
    deckCount = state.deckCount[player];
    handCount = state.handCount[player];
    
    printf("\nPreconditions:\n");
    printf("\tDeck Count: %d\n", deckCount);
    printf("\tHand Count: %d\n", handCount);
    
    
    // TEST of the basic hand and deckcount
    drawCard(player, &state);
    
    printf("\nPostconditions:\n");
    printf("\tDeck Count: %d\n", state.deckCount[player]);
    printf("\tHand Count: %d\n", state.handCount[player]);
    
    if(state.deckCount[player] == deckCount - 1){ // deck should decrease by 1
        printf("Deck Count test PASSED.\n");
    }
    else{
        printf("Deck Count test FAILED: Expected: %d.\n", (deckCount - 1));
    }
    
    if(state.handCount[player] == handCount + 1){ // hand should increase by 1
        printf("Hand Count test PASSED.\n");
    }
    else{
        printf("Hand Count test FAILED: Expected: %d.\n", (deckCount - 1));
    }
    
    
    
    
    
    // TEST if shuffle condition occured
    state.deckCount[player] = 0;
    state.discardCount[player] = 5;
    
    deckCount = state.deckCount[player];
    handCount = state.handCount[player];
    discardCount = state.discardCount[player];
    
    printf("\nPreconditions:\n");
    printf("\tDeck Count: %d\n", deckCount);
    printf("\tHand Count: %d\n", handCount);
    printf("\tDiscard Count: %d\n", discardCount);
    
    drawCard(player, &state);
    
    printf("\nPostconditions:\n");
    printf("\tDeck Count: %d\n", state.deckCount[player]);
    printf("\tHand Count: %d\n", state.handCount[player]);
    printf("\tDiscard Count: %d\n", state.discardCount[player]);
    
    
    if(state.discardCount[player] == 0 && state.deckCount[player] == discardCount - 1){ // discard should be 0 after shuffle. deckCount is the discard pile - 1, because the player drew a card
        printf("Discard Count test PASSED.\n");
    }
    else{
        printf("Discard Count test FAILED.\n");
    }
    
    
    
    return 0;
}


