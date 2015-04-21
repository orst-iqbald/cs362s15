/*----------------------------------------------
* testing smithy
*
* testcard1: cardtest1.c dominion.o rngs.o
*  gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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
    int i, r, j, count;
    int fail = 0;
    int numPlayer = 3;
    int seed = 1234;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    r = initializeGame(numPlayer, k, seed, G);

    for(i = 0; i < numPlayer; i++){
      G->whoseTurn = i;
      // store hand count
      count = G->handCount[i]; 
      smithy_refact(i, 0, G);
      if(G->handCount[i] != (count+2)){
        fail = 1;
        printf("smithy card returned an incorrect handcount %d, should be %d\n", G->handCount[i], count+2);
      }
    }
    if(!fail)    
      printf("All tests passed!\n");

  return 0;
}