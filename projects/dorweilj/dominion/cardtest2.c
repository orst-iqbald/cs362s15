/*----------------------------------------------
* testing minion_refact
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
    int i, r, j, m, actions, count, fail, choice1, choice2, coins;
    int cards[3];
    int numTests = 20;
    int numPlayer = 3;
    int seed = 1234;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    r = initializeGame(numPlayer, k, seed, G);
    srand(time(NULL));
    fail = 0;

    printf ("TESTING minion_refact():\n");
    for(i = 0; i< numTests; i++){

      r = initializeGame(numPlayer, k, seed, G);
      // random choice, both being sent doesn't make sense so no need to test that
      choice1 = rand() % 2;
      choice2 = !choice1;

      // set a random player
      G->whoseTurn = rand() % numPlayer;

      // store card count for player
      count = rand() % 10+1;
      G->handCount[G->whoseTurn] = count;

      // store the other players card counts
      for(m = 0; m < numPlayer; m++){
        if(m != G->whoseTurn){
          cards[m] = G->handCount[m];
        }
      }

      actions = G->numActions;
      coins = G->coins;

      minion_refact(choice1, choice2, G, 0);
      
      // check that state is incremented
      if(G->numActions != actions+1){
        printf("Number of actions incorrect: %d\tshould be: %d\n", G->numActions, actions+1);
        fail = 1;
      }
      // choice1: coins+2
      if(choice1 && (G->coins != coins+2)){
        printf("Number of coins incorrect: %d\t should be:%d\n", G->coins, coins+2);
        fail = 1;
      }
      // choice2: discard hand, redraw 4, other player discards/draws4 if they have > 5 cards
      if(choice2){
        for(j = 0; j < numPlayer; j++){
          if((G->whoseTurn == j) && (G->handCount[j] != 4)){
            printf("current player handCound incorrect: %d\t should be:%d\n", G->handCount[G->whoseTurn], 4);
            fail = 1;
          }
          else {
            if(cards[j] >= 5 && G->handCount[j] != 4){
              printf("other player handCound incorrect: %d\t should be:%d\n", G->handCount[j], 4);
              fail = 1;
            }
          }          
        }
      }

    }
    if(!fail)    
      printf("All tests passed!\n");

  return 0;
}