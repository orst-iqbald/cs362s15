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

int num_treasure(struct gameState *state){
  int treasureCount = 0;
  int j = 0;
  for(j = 0; j< state->handCount[0]; j++){
    int card = state->hand[0][j];
    if(card == copper || card == silver || card == gold){
      treasureCount++;
    }
  }
  return treasureCount;
}

int main () {

    int i, r, j, m, fail, setshuffle, treasureCount, treasureCount2;
    int cards[3];
    int numTests = 100;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    fail = 0;
    int seed = floor((Random() * 2341) + 1);

    PutSeed((long)seed);
    
    printf ("Random testing adventurer_refact():\n");
    for(i = 0; i< numTests; i++){
      printf( "\nStarting test %d", i);

      struct gameState *G = malloc(sizeof(struct gameState));
      seed = floor((Random() * 2341) + 1);
      // set a random number of players at least two
      int players = floor((Random()*3)+2);
      int num_treasure_in_deck;

      initializeGame(players, k, seed, G);

      // set some random values for the playergameState G
      G->whoseTurn = 0;
      G->playedCardCount = floor(Random()*5);
      G->handCount[0] = floor(Random() * (MAX_HAND / 3));
      
      // deck needs to have a few cards or things blow up
      G->deckCount[0] = floor(Random()*(MAX_DECK / 3)+2);
      G->discardCount[0] = floor(Random()*(MAX_DECK / 3));

      // set up a random deck
      for(j = 0; j < G->deckCount[0]; j++){
        G->deck[0][j] = floor(Random() * 17);
      }

      // give the player some random cards
      for(j = 0; j < G->handCount[0]; j++){
        G->hand[0][j] = floor(Random() * 17);
      }

      // set some random discard cards
      for(j = 0; j < G->discardCount[0]; j++){
        G->discard[0][j] = floor(Random() * 17);
      }

      // save the current state of the game before we start messing with stuff
      struct gameState *savedState = malloc(sizeof(struct gameState));
      memcpy(savedState, G, sizeof(struct gameState));

      adventurer_refact(0, G);

      // check treasure count
      int expected = (num_treasure(savedState) + 2);
      if(num_treasure(G) != expected){
        printf("\n fail! treasure count with value: %d expected: %d\n", treasureCount, expected);
        fail=1;
      }

      // check hand count
      if(G->handCount[0] != (savedState->handCount[0] + 2)){
        printf("\n fail! handCount with value: %d expected: %d\n", G->handCount[0], (savedState->handCount[0] + 2));
        fail=1;
      }

      printf("....... Passed \n");
      free(G);
      free(savedState);
}
    if(!fail)    
      printf("All tests passed!\n");

  return 0;
}