//  Ian Taylor
//  CS 362 - Assignment 4
//  randomtestcard.c: smithyCard() random tester
//
//




#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#include <time.h>
#include <stdlib.h>

#include <assert.h>
#include "rngs.h"


int main(){
    srand(time(NULL)); // seed random generator
    
    int i, r, numCards, numActions;
    int seed = 1000;
    
    int numPlayer = 2; // numPlayer is randomized later on
    int next_turn = 0; // next_turn used to cycle through turns when numPlayer > 2
    int handPos = 0; // also randomized in for-loop below
    
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    int fail_count = 0;
    int test_number = 0; // tracks current test number

    
    numPlayer = (rand() % 3) + 2; // numPlayers randomized in range 2-4
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    printf ("RANDOM TESTS FOR: smithyCard():\n");
    
    
    // RANDOM TESTER
    for(i = 0; i < 200; i++){
        
        
        handPos = (rand() % 7); // handPos in range 0 - 6

     
        
        state.hand[whoseTurn(&state)][0] = smithy; // player has smithy card in hand
        numCards = state.handCount[whoseTurn(&state)]; //Get the number of cards in the player's hand
        numActions = state.numActions; // get the current number of actions
        
        // call the smithy card using randomized handPos
        smithyCard(&state, whoseTurn(&state), 0);
        
        
        // ERROR REPORTS: //
        
        // INCORRECT CARD NUMBER
        if(state.handCount[whoseTurn(&state)] != numCards + 2){
            // report test#, Current Player, and HandPos
            printf("FAIL \tIncorrect Number of Cards \tTest: #%d \tCurrent Player: %d \thandPos: %d\n", test_number, whoseTurn(&state), handPos);
            
            fail_count += 1;
        }
        // INCORRECT ACTION NUMBER
        if(state.numActions != numActions){ // state.numActions does not yet decrement, but should not increase either
            // report test#, Current Player, and HandPos
            printf("FAIL \tIncorrect Number of Actions \tTest: #%d \tCurrent Player: %d \thandPos: %d\n", test_number, whoseTurn(&state), handPos);
            
            fail_count += 1;
        }
        
        endTurn(&state); // end current player's turn
        
        
        //next_turn += 1;
        test_number += 2; // increment by 2 b/c we ran two tests in each iteration: one for cards, one for actions
    }
    
    printf("Failed %d out of %d tests\n", fail_count, test_number);
    
    
    
    return 0;
}


