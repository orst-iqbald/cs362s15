/*----------------------------------------------
* testing shuffle
*
* testShuffle: unittest2.c dominion.o rngs.o
*      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*
*-----------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {

    struct gameState *G = malloc(sizeof(struct gameState));
    int i, r;
    int seed = 1000;
    int numTests = 10;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    printf ("TESTING shuffle():\n");
    for(i = 0; i < numTests; i++){
        // initialize a new game
        r = initializeGame(numPlayer, k, seed, G);
        assert(r == 0);

        // copy player 2 deck into player one deck.  They now both have the same cards
        memcpy(G->deck[0], G->deck[1], sizeof(G->deck[0]));

        // compare the two decks.  They should be the same
        r = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
        assert( r == 0);

        // shuffle player 1
        r = shuffle(0, G);
        assert(r == 0);

        // compare player 1 and player 2 decks.  They should be different now
        r = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
        assert( r != 0);

        // shuffle player 2
        r = shuffle(1, G);
        assert(r == 0);

        // compare player 1 and player 2 decks.  They should still be different
        r = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
        assert( r != 0);
    }    

    printf("All tests passed!\n");

    return 0;
}