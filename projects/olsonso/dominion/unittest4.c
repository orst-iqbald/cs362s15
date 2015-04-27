//Testing buyCard

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main () {
    struct gameState *G = malloc(sizeof(struct gameState));
    int i, start, j, cost, firstBuys, firstCoins;
    int numTests = 10;
    int numPlayer = 2;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};  
    
    srand(time(NULL));
    printf ("Testing to check buyCard():\n"); 


    for(i = 0; i < numTests; i++){
      // test all 10 cards in array k
      for(j = 0; j < 10; j++){
        // start with new game 
        start = initializeGame(numPlayer, k, seed, G);
        G->numBuys = rand() % 9;
        // this will store the first set of buys. 
        firstBuys = G->numBuys;
        G->supplyCount[j] = rand() % 9;
        G->coins = rand() % 9;
        firstCoins = G->coins;
        cost = getCost(k[j]);

        // test buyCard and then use that to compare the first one.
        start = buyCard(k[j], G);
        //start comparasion 
        if(G->supplyCount[j] > 0 && firstBuys && firstCoins >= cost){
          assert(start == 0);

          // check game state after buying
          //should be 
          assert(G->numBuys < firstBuys);
          assert(G->coins < firstCoins);

        } else {
          assert(start== -1);
        }
      }
    }
    printf("Done testing, success was achieved. \n");

  return 0;
}