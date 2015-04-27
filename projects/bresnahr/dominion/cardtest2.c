#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//cardtest2.c tests the adventure card
int main(){

    int fail = 0;
    int card, np, i, x;
    int seed = 1000;
    int numberPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int handCount, newHandCount, treasureCount, newTreasureCount;

    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);

    for(np = 0; np < numberPlayers; np++){
     
      treasureCount = 0;
      newTreasureCount = 0;
      newHandCount = 0;
      x = 1;

      myGameState->hand[np][0] = adventurer;

      if(myGameState->handCount[np] >= 4){
        myGameState->hand[np][x] = gold;
	myGameState->hand[np][x+1] = silver;
	myGameState->hand[np][x+2] = copper;
      }

      for(i = 0; i < myGameState->handCount[np]; i++){
 	card = myGameState->hand[np][i];
        if(card == copper || card == silver || card == gold){
	  treasureCount++;
	}
      }

      handCount = myGameState->handCount[np];
      newAdventurer(np, myGameState);
      newHandCount = myGameState->handCount[np];


      for(i = 0; i < myGameState->handCount[np]; i++){
        card = myGameState->hand[np][i];
        if(card == copper || card == silver || card == gold){
          newTreasureCount++;
        }
      }
      
      printf("Hand count before adventurer %d, after %d, expected after %d\n", handCount, newHandCount, handCount+2); 
      if(handCount+2 != newHandCount){
	printf("Test failed\n");
        fail++;
      }

      printf("Treasure card count after adventurer called %d, expected %d\n", newTreasureCount, (treasureCount+2));
      if(newTreasureCount != (treasureCount+2)){//check if treasure count before adventurer callis is less two than after card is called
        printf("Test failed\n");
	fail++;
      }
    }
    
   free(myGameState);
    
   if(fail == 0){
     printf("All tests passed!\n"); 
   }
return 0;
}
