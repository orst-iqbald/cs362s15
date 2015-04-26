#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//unittest3 test for fullDeckCount() checks decks of players, game is initialized with copper and estate cards, therefore this test, test this state only
int main(){

    int fail = 0;
    int myDeckCount, i, player, myCount; 
    int numberPlayers = 2;
    int seed = 1000;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int deckCards[2] = {copper, estate};// players deck is initialized with copper and estates only
    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);

    for(player = 0; player < numberPlayers; player++){
   
      myCount = 0;
      myDeckCount = 0;
      for (i = 0; i < myGameState->deckCount[player]; i++){
        if(myGameState->deck[player][i] == deckCards[0] || myGameState->deck[player][i] == deckCards[1]) myCount++;
      }

      for (i = 0; i < myGameState->handCount[player]; i++){
        if (myGameState->hand[player][i] == deckCards[0] || myGameState->hand[player][i] == deckCards[1]) myCount++;
      }

      for (i = 0; i < myGameState->discardCount[player]; i++){
        if(myGameState->discard[player][i] == deckCards[0] || myGameState->discard[player][i] == deckCards[1]) myCount++;
      }
      
      myDeckCount = fullDeckCount(player, copper, myGameState);
      myDeckCount += fullDeckCount(player, estate, myGameState);
      printf("Full deck count is %d, expected %d for player %d\n", myDeckCount, myCount, player);
      if(myDeckCount != myCount){//cehck if the count of vicory cards and coins is the same
        printf("Test failed\n");
        fail++;
      }
    }

    if(fail == 0){
      printf("All tests passed!\n");
    }

    free(myGameState);

return 0;
}
