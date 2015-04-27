#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//unittest4 this tests shuffle() which randomizes the order of the players deck
int shuffleCompare(const void* a, const void* b){
  if(*(int*)a > *(int*)b)
    return 1;
  if(*(int*)a < *(int*)b)
    return -1;
  return 0;
}
int main(){

    int fail = 0;
    int player, before, after;
    int numberPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;

    struct gameState *myGameState = malloc(sizeof(struct gameState));;
    struct gameState *postGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, postGameState);
    
    memcpy(myGameState, postGameState, sizeof(struct gameState));//copy myGameState to postGameState
    before = 0;
    
    for(player = 0; player < numberPlayers; player++){
      after = shuffle(player, postGameState);
    
     
      if(myGameState->deckCount[player] < 1){//check if deckCount was populated
        printf("Deck count was not populated, test failed\n");
        fail++;
      }
      qsort ((void*)(myGameState->deck[player]), myGameState->deckCount[player], sizeof(int), shuffleCompare);
    
      printf("Value of game state after shuffle %d, expected %d\n", after, before);
      if(after != before){//check if shuffle returns same value between game states
        printf("Test failed\n");
        fail++;
      }    

      printf("Value of player's deck after shuffle %d, before shuffle %d\n", *postGameState->deck[player], *myGameState->deck[player]);
      if(myGameState->deck[player] == postGameState->deck[player]){
        printf("Test failed\n");
        fail++;
      }
    }

    free(postGameState);
    free(myGameState);
 
    if(fail == 0){
      printf("All tests passed!\n");
    }

return 0;
}
