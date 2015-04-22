/*----------------------------------------------
* testing buyCard
*
* testbuy: unittest4.c dominion.o rngs.o
*      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
*
*-----------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {
    struct gameState *G = malloc(sizeof(struct gameState));
    int i, r, j, preCoins, cost, preBuys;
    int numTests = 10000;
    int numPlayer = 2;
    int seed = 1234;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    srand(time(NULL));
    
    // buyCard first checks to see that the player has buys     
    for(i = 0; i < numTests; i++){
      // test all the cards
      for(j = 0; j < 10; j++){
        // initialize a new game
        r = initializeGame(numPlayer, k, seed, G);
        // test rand buy number from 0-10
        G->numBuys = rand() % 10 + 1;
        // store buys since it changes after calling buyCard
        preBuys = G->numBuys;

        // set a random suppy number for the card
        G->supplyCount[j] = rand() % 5 + 1;
        
        // set the number of coins
        G->coins = rand() % 30 + 1;
        preCoins = G->coins;

        // get the cost for the card
        cost = getCost(k[j]);

        // test buyCard
        r = buyCard(k[j], G);

        //printf("supply %d\t buys%d\t cost%d\t coins%d\n",G->supplyCount[j], preBuys, cost, preCoins);
        
        // Test the result
        if(G->supplyCount[j] > 0 && preBuys && preCoins >= cost){
          //printf("Assert 0\n");
          assert(r == 0);

          // check game state after buying
          assert(G->numBuys < preBuys);
          assert(G->coins < preCoins);
          
        } else {
          //printf("Assert -1\n");
          assert(r == -1);
        }
      }
    }
    printf("All tests passed!\n");

  return 0;
}