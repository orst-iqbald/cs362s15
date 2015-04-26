#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testSmithyFunc() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    int dummyHand[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        dummyHand[0] = curse; 
        dummyHand[1] = gold;
        dummyHand[2] = smithy;
        dummyHand[3] = adventurer;
        dummyHand[4] = village;
    }

    int handPos = 2; // location of smithy in hand
    handCount = 5;

    printf ("TESTING smithyFunc():\n");
    for (p = 0; p < numPlayer; p++)
    {
        
        printf("Test player %d.\n", p);
               
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[p] = handCount;                 //  set the number of cards on hand

        memcpy(G.hand[p], dummyHand, sizeof(int) * handCount); // set cards to dummy hand
        smithyFunc(&G, p, handPos);

        // check if we have 2 more cards (3 added and 1 discarded)
        if(G.handCount[p] == handCount + 2) 
          printf("PASSED: 3 cards added\n");
        else
          printf("FAIL: 3 cards added\n");
      
    }
}

int main(int argc, char *argv[])
{
    testSmithyFunc();

    return 0;
}
