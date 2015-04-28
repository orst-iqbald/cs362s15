#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

#define TESTFUNC "IsGameOver()"

int main() {
    
    int i;    
    int seed = 1000;
    int numPlayer = 2;
    int supplyPiles = 24;
    
    struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    
    //Setting up game state to prepare and player cards
    initializeGame(numPlayer, k, seed, &state);
    
    //Testing if game is still going
    printf("Asserting game state is not over.\n");
    assert(isGameOver(&state) == 0);

    //reset the game state
    memset(&state, 23, sizeof(struct gameState));

    for (i = 0; i <= supplyPiles; i++) {
        printf("Asserting game ends when supply piles are empty.\n");
        state.supplyCount[i] = 0;
        if (i < 2){
       	//Asserts game is not over if supply piles are not empty
        assert(isGameOver(&state) == 0);
    	}else{
        //Asserts the game is over when 3 or more piles are empty.
        assert(isGameOver(&state) == 1);
    	}
    }
    
    printf("Asserting game is over if there are no province cards.\n");

    //reset the game state
    memset(&state, 23, sizeof(struct gameState));
    
    //Set province cards to zero.
    state.supplyCount[province] = 0;
    assert(isGameOver(&state) == 1);
    
    printf("Game over tests passed.\n");
    
    return 0;
}