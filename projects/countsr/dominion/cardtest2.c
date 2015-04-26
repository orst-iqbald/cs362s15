#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testAdventurerFunc() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int coinCount;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    // arrays of all estates
    int duchys[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        duchys[i] = duchy; 
    }

    printf ("TESTING adventurerFunc():\n");
    for (p = 0; p < numPlayer; p++)
    {
      printf("Test player %d.\n", p);
        for (handCount = 1; handCount <= maxHandCount; handCount++) // 5 cards
        { 
                coinCount = 0;
                
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 //  set the number of cards on hand

                
                memcpy(G.hand[p], duchys, sizeof(int) * handCount); // set all the cards to estates
                adventurerFunc(&G, p);
              
                // check if hand has 2 treasure cards              
                for(i=0; i < handCount+2; i++) {
                    if(G.hand[p][i] == gold || G.hand[p][i] == silver || G.hand[p][i] == copper){
                      coinCount++;
                    }
                }

                if(coinCount == 2)
                  printf("PASSED: 2 treasure cards added\n");
                else
                	printf("FAIL: 2 treasure cards added\n");
            
        }      
    }


    
}

int main(int argc, char *argv[])
{
    testAdventurerFunc();

    return 0;
}