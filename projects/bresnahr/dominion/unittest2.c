#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//unittest2 for updateCoins()  number of coins + bonus in hand should be updated to the coin variable in the game state (state->coins)
void coinCount(struct gameState** myGameState);
int main(){

    int fail = 0;    
    int np, i, bonus;
    int numberPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int maxBonus = 10;

    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);

    np = myGameState->whoseTurn;
    bonus = maxBonus;
    myGameState->coins = 0;
     
    for(i = 0; i < myGameState->handCount[np]; i++){
      myGameState->hand[np][i] = copper;
    }        
    coinCount(&myGameState); 
    updateCoins(np, myGameState, bonus);
    printf("Hand all copper: number of coins in my game %d, expected number of coins %d\n", myGameState->coins, (myGameState->handCount[np] * 1 + bonus));
    if(myGameState->coins != (myGameState->handCount[np] * 1 + bonus)){
      printf("Test failed\n");
      fail++;
    }

    for(i = 0; i < myGameState->handCount[np]; i++){
      myGameState->hand[np][i] = silver;
    }
    coinCount(&myGameState);
    updateCoins(np, myGameState, bonus);
    printf("Hand all silver: number of coins in my game %d, expected number of coins %d\n", myGameState->coins, (myGameState->handCount[np] * 2 + bonus));
    if(myGameState->coins != (myGameState->handCount[np] * 2 + bonus)){
      printf("Test failed\n");
      fail++;
    }


    for(i = 0; i < myGameState->handCount[np]; i++){
      myGameState->hand[np][i] = gold;
    }
    coinCount(&myGameState);
    updateCoins(np, myGameState, bonus);
    printf("Hand all gold: number of coins in my game %d, expected number of coins %d\n", myGameState->coins, (myGameState->handCount[np] * 3 + bonus));
    if(myGameState->coins != (myGameState->handCount[np] * 3 + bonus)){
      printf("Test failed\n");
      fail++;
    }


    if(fail == 0){
      printf("All tests passed!\n");
    }
  
    free(myGameState);

return 0;
}
void coinCount(struct gameState** myGameState){
    int i;

    for(i = 0; i < (*myGameState)->handCount[(*myGameState)->whoseTurn]; i++){
      if((*myGameState)->hand[(*myGameState)->whoseTurn][i] == copper){
        (*myGameState)->coins += 1;
      }
      if((*myGameState)->hand[(*myGameState)->whoseTurn][i] == silver){
        (*myGameState)->coins += 2;
      }
      if((*myGameState)->hand[(*myGameState)->whoseTurn][i] == gold){
        (*myGameState)->coins += 3;
      }
    }
}
