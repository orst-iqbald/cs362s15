//  Ian Taylor
//  CS 362 - Assignment 4
//  randomtestcard.c: adventurerCard() random tester
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
    
    int i, j, r, numCards, numActions;
    int initialTreasure = 0; // used to verify amount of treasure drawn
    int postTreasure = 0;

    int seed = 1000;
    
    int numPlayer = 2; // numPlayer is randomized later on
    int next_turn = 0; // next_turn used to cycle through turns when numPlayer > 2
    int handPos = 0; // also randomized in for-loop below
    
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    // test variables for adventurerCard
    int drawntreasure = 0;
    int cardDrawn = 0;
    int temphand[MAX_HAND];
    int z = 0;
    
    
    int fail_count = 0;
    int test_number = 0; // tracks current test number

    
    numPlayer = (rand() % 3) + 2; // numPlayers randomized in range 2-4
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    printf ("RANDOM TESTS FOR: adventurerCard():\n");
    
    
    // RANDOM TESTER
    for(i = 0; i < 200; i++){
        initialTreasure = 0;
        postTreasure = 0;
        
        // randomize handpos and drawntreasure
        handPos = (rand() % 7); // handPos in range 0 - 6
        drawntreasure = (rand() % 3); // drawntreasure 0 - 2
        
         state.hand[whoseTurn(&state)][0] = adventurerCard; // player has adventurer card in hand
        
        // calculate the initialTreasure in player's hand
        for(j = 0; j < state.handCount[whoseTurn(&state)]; j++){
            if(state.hand[whoseTurn(&state)][i] == copper || state.hand[whoseTurn(&state)][i] == silver || state.hand[whoseTurn(&state)][i] == gold){
                initialTreasure += 1;
            }
        }
        
    
        // call the adventurer card using randomized handPos, drawntreasure, etc.
        // if drawntreasure >= 2, we expect no change
        adventurerCard(&state, whoseTurn(&state), handPos, drawntreasure, cardDrawn, temphand, z);

        // calculate the postTreasure in player's hand
        for(j = 0; j < state.handCount[whoseTurn(&state)]; j++){
            if(state.hand[whoseTurn(&state)][i] == copper || state.hand[whoseTurn(&state)][i] == silver || state.hand[whoseTurn(&state)][i] == gold){
                postTreasure += 1;
            }
        }

        
        // ERROR REPORTS: //
        
        // INCORRECT TREASURE NUMBER
        if((drawntreasure >= 2) && (postTreasure != initialTreasure)){
            printf("FAIL \tIncorrect Treasure \tTest: #%d \tCurrent Player: %d \thandPos: %d \tdrawnTreasure \tinitialTreasure %d \tpostTreasure %d\n", test_number, whoseTurn(&state), handPos, drawntreasure, initialTreasure, postTreasure);
            
            fail_count += 1;
        }
        else if((drawntreasure == 1) && (postTreasure != initialTreasure + 1)){
            printf("FAIL \tIncorrect Treasure \tTest: #%d \tCurrent Player: %d \thandPos: %d \tdrawnTreasure %d \tinitialTreasure %d \tpostTreasure %d\n", test_number, whoseTurn(&state), handPos, drawntreasure, initialTreasure, postTreasure);
            
            fail_count += 1;
        }
        else if((drawntreasure == 0) && (postTreasure != initialTreasure + 2)){
            printf("FAIL \tIncorrect Treasure \tTest: #%d \tCurrent Player: %d \thandPos: %d \tdrawnTreasure %d \tinitialTreasure %d \tpostTreasure %d\n", test_number, whoseTurn(&state), handPos, drawntreasure, initialTreasure, postTreasure);
            
            fail_count += 1;
        }

        
        
        endTurn(&state); // end current player's turn
        
        
        
        test_number += 1; // increment by 2 b/c we ran two tests in each iteration: one for cards, one for actions
    }
    
    printf("Failed %d out of %d tests\n", fail_count, test_number);
    
    
    
    return 0;
}


