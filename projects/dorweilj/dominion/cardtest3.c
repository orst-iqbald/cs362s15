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
    int i, r, j, m, fail, setshuffle, treasureCount, treasureCount2;
    int cards[3];
    int numTests = 10;
    int numPlayer = 3;
    int seed = 1234;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    srand(time(NULL));
    fail = 0;
    r = initializeGame(numPlayer, k, rand()%1000+1, G);
    for(i = 0; i< numTests; i++){
      printf("testing %d\n",i);
      treasureCount = 0;
      treasureCount2 = 0;
  
      // check the players hand
      for(j = 0; j< G->handCount[0]; j++){
        int card = G->hand[0][j];
        if(card == copper || card == silver || card == gold){
          treasureCount++;
        }
      }
      adventurer_refact(0, G);

            // check the players hand after.  should more 2 more treasure cards
      for(j = 0; j< G->handCount[0]; j++){
        int card = G->hand[0][j];
        if(card == copper || card == silver || card == gold){
          treasureCount2++;
        }
      }

      if(treasureCount != treasureCount2-2){

        printf("stuff failed!\n");

      }
      // test results
      if(setshuffle){
        printf("Shuffle failed\n");
        fail = 1;
      }


}
    if(!fail)    
      printf("All tests passed!\n");

  return 0;
}