//  Ian Taylor
//  CS 362 - Assignment 3
//  cardtest4.c: adventurerCard() test
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"




int main(){
    
    int i, r, numCards;
    int numTreasure = 0; // used to verify amount of treasure drawn
    int seed = 1000;
    int numPlayer = 2;
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    
    struct gameState state;
    
    
    // test variables for adventurerCard
    int handPos = 0;
    int drawntreasure = 0;
    int cardDrawn = 0;
    int temphand[MAX_HAND];
    int z = 0;
    
    
    printf ("TESTING adventureCard():\n");
    
    memset(&state, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    
    
    // PLAYER 1 TESTS
    
    state.hand[whoseTurn(&state)][0] = adventurer; // player has great_hall card in hand
    numCards = state.handCount[whoseTurn(&state)]; // get the current number of cards in player's hand
    
    
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){ // set all cards to adventurer cards, i.e. the player is not holding any treasure
        state.hand[whoseTurn(&state)][i] = adventurer;
    }
    
    
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){ // set all cards to adventurer cards, i.e. the player is not holding any treasure
        if(state.hand[whoseTurn(&state)][i] == copper || state.hand[whoseTurn(&state)][i] == silver || state.hand[whoseTurn(&state)][i] == gold){
            numTreasure++;
        }
    }
    
    printf("\nPreconditions: \n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tInitial HandCount: %d\n", numCards);
    printf("\tInitial Treasure Amount: %d\n", numTreasure);
    
    // play the adventurer card
    adventurerCard(&state, whoseTurn(&state), handPos, drawntreasure, cardDrawn, temphand, z);
    
    
    numTreasure = 0;
    
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){ // set all cards to adventurer cards, i.e. the player is not holding any treasure
        if(state.hand[whoseTurn(&state)][i] == copper || state.hand[whoseTurn(&state)][i] == silver || state.hand[whoseTurn(&state)][i] == gold){
            numTreasure++;
        }
    }
    
    
    numCards = state.handCount[whoseTurn(&state)];
    
    printf("\nPostconditions: \n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tSubsequent HandCount: %d\n", numCards);
    printf("\tSubsequent Treasure Amount: %d\n", numTreasure);
    
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    endTurn(&state); // end current player's turn
    
    
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    
    
    // PLAYER 2 TESTS
    
    state.hand[whoseTurn(&state)][0] = adventurer; // player has great_hall card in hand
    numCards = state.handCount[whoseTurn(&state)]; // get the current number of cards in player's hand
    
    
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){ // set all cards to adventurer cards, i.e. the player is not holding any treasure
        state.hand[whoseTurn(&state)][i] = adventurer;
    }
    
    
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){ // set all cards to adventurer cards, i.e. the player is not holding any treasure
        if(state.hand[whoseTurn(&state)][i] == copper || state.hand[whoseTurn(&state)][i] == silver || state.hand[whoseTurn(&state)][i] == gold){
            numTreasure++;
        }
    }
    
    printf("\nPreconditions: \n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tInitial HandCount: %d\n", numCards);
    printf("\tInitial Treasure Amount: %d\n", numTreasure);
    
    // play the adventurer card
    adventurerCard(&state, whoseTurn(&state), handPos, drawntreasure, cardDrawn, temphand, z);
    
    
    numTreasure = 0;
    
    for(i = 0; i < state.handCount[whoseTurn(&state)]; i++){ // set all cards to adventurer cards, i.e. the player is not holding any treasure
        if(state.hand[whoseTurn(&state)][i] == copper || state.hand[whoseTurn(&state)][i] == silver || state.hand[whoseTurn(&state)][i] == gold){
            numTreasure++;
        }
    }
    
    
    numCards = state.handCount[whoseTurn(&state)];
    
    printf("\nPostconditions: \n");
    printf("\tCurrent Player: %d\n", whoseTurn(&state));
    printf("\tSubsequent HandCount: %d\n", numCards);
    printf("\tSubsequent Treasure Amount: %d\n", numTreasure);
    

    return 0;
}