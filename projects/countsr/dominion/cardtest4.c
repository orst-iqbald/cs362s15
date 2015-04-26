#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testRemodelFunc() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int c1, c2, c3;
    int coinCount;
    int test1 = 0;
    int test2 = 0;
    int p, r, handCount;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int dummyHand[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        dummyHand[0] = curse; 
        dummyHand[1] = gold;
        dummyHand[2] = smithy;
        dummyHand[3] = adventurer;
        dummyHand[4] = village;
    }

    int handPos = 2; // location of smithy that we will trash
    handCount = 5;

    int preCoins;
    int preHandCount;

    printf ("TESTING remodelFunc():\n");
    for (p = 0; p < numPlayer; p++)
    {
                coinCount = 0;
                printf("Test player %d.\n", p);
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
               
                
            
                G.handCount[p] = handCount;                 //  set the number of cards on hand
                preCoins = G.coins;
                memcpy(G.hand[p], dummyHand, sizeof(int) * handCount); 
                remodelFunc(&G, p, handPos, dummyHand[2], mine); //trash smithy and add mine

                for(i=0; i < handCount; i++) {
                    if(G.hand[p][i] == dummyHand[2]) // is trashed card still in hand
                        test1 = 1;
                }
                if(test1 == 1) 
                    printf("FAIL: Choice 1 was trashed \n");
                else
                    printf("PASS: Choice 1 was trashed\n");


                
                if(G.discard[p][G.discardCount[p]-1] == 11) // is card2  added to discardPile -- (11 = mine card)
                    test2 = 1;
                
                
                if(test2 == 1) // 
                    printf("PASS: Choice 2 was added\n");
                else
                    printf("FAIL: Choice 2 was added \n");
      
    }
}

int main(int argc, char *argv[])
{
    testRemodelFunc();

    return 0;
}