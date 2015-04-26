//*************************************
//Testing to check the shuffle function in game
//*************************************


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(){
	struct gameState *G = malloc(sizeof(struct gameState));
    int i, r;
    int seed = 1000;
    int numTests = 10;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    

printf ("Testing shuffle function.\n");   
  
//First, initalize new game

      for(i = 0; i < numTests; i++){
        // initialize a new game
        r = initializeGame(numPlayer, k, seed, G);
        assert(r == 0);

//Copy the deck and create a second deck
      	memcpy(G->deck[0], G->deck[1], sizeof(G->deck[0]));

// compare the two decks.  They should be the same
        r = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
        assert( r == 0);

// shuffle 1 deck
        r = shuffle(0, G);
        assert(r == 0);

//shuffle 2nd deck
        r = shuffle(1, G);
        assert(r == 0);

// compare deck 1 and 2.  They should be different
        r = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
        assert( r != 0);
    }    

    printf("All tests passed!\n");

    return 0;
}
