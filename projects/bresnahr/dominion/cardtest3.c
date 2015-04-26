#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//card test 3 for village card
//card perks are to draw a card and gives player 2 extra actions.  The village card is then discarded
//test checks if player drew another card, if number of available actions is +2 and if the village card was discarded
int main(){
    int fail = 0;
    int np, preActions, preHandCount;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int numberPlayers = 2;

    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);

    for(np = 0; np < numberPlayers; np++){

      printf("Player %d\n", np);
      preActions = myGameState->numActions;
      preHandCount = myGameState->handCount[np];
      myGameState->hand[np][0] = village;
      newVillage(np, myGameState, 0);      
    
      if(myGameState->handCount[np] != preHandCount){//check if +1 card was added
        printf("1 card was not added to hand, test failed\n");
	fail++;
      }else{
        printf("1 card was added to hand using village card\n");
      }

      printf("Number of actions before card played %d, after %d, expected after %d\n", preActions,  myGameState->numActions, preActions+2);
      if(myGameState->numActions != preActions+2){//check if 2 actiosn were added
        printf("Test failed\n");
	fail++;
      }

      if(myGameState->hand[np][0] == village){//check if village card was discarded from hand
        printf("Village card was not discarded, test failed\n");
        fail++;
      }else{
	printf("Village card was discarded\n");
      }
    }
      free(myGameState);
    
    if(fail == 0){
      printf("All tests passed!\n");
    }
return 0;
}
