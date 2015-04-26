/*----------------------------------------------
* testing adventurer_refact
*
* testcard3: cardtest3.c dominion.o rngs.o
*  gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    int numTests = 100;
    int numPlayer = 3;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    srand(time(NULL));
    fail = 0;
    
    printf ("TESTING adventurer_refact():\n");
    for(i = 0; i< numTests; i++){

      r = initializeGame(numPlayer, k, rand()%1000+1, G);

      treasureCount = 0;
      treasureCount2 = 0;

      // give the player a gold to start
      G->deck[0][G->handCount[0]-1] = gold;
  
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

      int expected = treasureCount + 2;
      if(treasureCount2 != expected){
        printf("fail! with value: %d expected: %d\n", treasureCount, expected);
        fail = 1;
      }
}
    if(!fail)    
      printf("All tests passed!\n");

  return 0;
}