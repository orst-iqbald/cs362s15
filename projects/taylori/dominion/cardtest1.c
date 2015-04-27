//  Ian Taylor
//  CS 362 - Assignment 3
//  cardtest1.c: smithyCard() test
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
    
    int i, r, numCards;
    int seed = 1000;
    int numPlayer = 2;
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;

    printf ("TESTING smithyCard():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    state.hand[whoseTurn(&state)][0] = smithy; // player has smithy card in hand
    numCards = state.handCount[whoseTurn(&state)]; //Get the number of cards in the player's hand
    
    
    // PLAYER 1 TESTS
    // Print hand before test
    printf("\nPreconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));

    
    // Call the Smithy Card
    smithyCard(&state, whoseTurn(&state), 0);
    
    printf("\nPostconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    
    // Player should have two more cards in their hand, because they discard the smithy card.
    if(state.handCount[whoseTurn(&state)] == numCards + 2) {
        printf("smithyCard() test PASSED.\n");
    }
    else {
        printf("smithyCard() test FAILED: incorrect number of cards in player's hand.\n");
    }

    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    
    endTurn(&state); // end current player's turn
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    state.hand[whoseTurn(&state)][0] = smithy; // player has smithy card in hand
    numCards = state.handCount[whoseTurn(&state)]; //Get the number of cards in the player's hand
    
    // PLAYER 2 TESTS
    // Print hand before test
    printf("\nPreconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));
    
    
    // Call the Smithy Card
    smithyCard(&state, whoseTurn(&state), 0);
    
    printf("\nPostconditions:\n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tHand Count: %d\n", numHandCards(&state));

    
    // Player should have two more cards in their hand, because they discard the smithy card.
    if(state.handCount[whoseTurn(&state)] == numCards + 2) {
        printf("smithyCard() test PASSED.\n");
    }
    else {
        printf("smithyCard() test FAILED: incorrect number of cards in player's hand.\n");
    }
    
    return 0;
}


