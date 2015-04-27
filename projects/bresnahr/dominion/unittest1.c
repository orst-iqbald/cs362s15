#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//unit test for function isGameOver()  checks if victory supply cards are either 0 or province supply is zero for game over conditions 
int main(){

    int fail = 0;
    int i, j;
    int numberPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;

    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);

    assert(myGameState->supplyCount[province] == 8);//check if supply province cards initialized to 8

    myGameState->supplyCount[province] = 0;
    printf("Number of province cards %d, expected 0\n", myGameState->supplyCount[province]);
    if(myGameState->supplyCount[province] != 0 && !isGameOver(myGameState)){//check if province supply is 0, therefore game over
      printf("Test failed\n");
      fail++;
    }

    j = 0;
    for(i = 0; i < 25; i++){
      if(myGameState->supplyCount[i] == 0)
        {
          j++;
        }
    }
    printf("Number of victory cards %d, expected number 0\n", j );
    if( j > 0 && !isGameOver(myGameState)){//check if all supply victory cards is 0, therefore game over
      printf("Test failed\n");
      fail++;
    }

    if(fail == 0){
      printf("All tests passed!\n");
    }

    free(myGameState);

return 0;
}
