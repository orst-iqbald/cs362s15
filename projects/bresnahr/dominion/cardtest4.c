#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//cardtest4 tests council_room card
int main(){

    int fail = 0;
    int i;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    int seed = 1000;
    int numberPlayers = 2;
    int newHandCount[numberPlayers];
    int numBuys;

    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);
   
    printf("Number of players: %d\n", myGameState->numPlayers);
 
    for(i = 0; i < myGameState->numPlayers; i++){//store number of cards in players hands before council card played
      newHandCount[i] = myGameState->handCount[i];
      printf("Player %d has %d cards in their hand\n", i+1, newHandCount[i]);
    }

    numBuys = myGameState->numBuys;//store number of buys before council card played 
    printf("Number of buys in current game state before council room played %d\n", numBuys);

    myGameState->hand[whoseTurn(myGameState)][0] = council_room;
    printf("Current player has %d cards before council room played\n", myGameState->handCount[myGameState->whoseTurn]);
    newCouncil_room(myGameState->whoseTurn, myGameState, 0); 
    
    printf("Number of cards in current hand after council room played %d, expected %d\n", numHandCards(myGameState), newHandCount[myGameState->whoseTurn]+3);
    if(myGameState->handCount[myGameState->whoseTurn] != newHandCount[myGameState->whoseTurn]+3){//check if 4 cards were added and 1 discarded in hand that played council room
      printf("4 cards were not added to current hand, test failed\n");
      fail++;
    }else{
      printf("4 cards were added to current hand, test passed\n");
    }
   
    printf("Number of buys after playng council room card %d, expected %d\n", myGameState->numBuys, numBuys+1); 
    if(myGameState->numBuys != (numBuys + 1)){//if number of buys was not incremented by 1
      printf("Test failed\n");
      fail++;
    }

    for(i = 0; i < myGameState->numPlayers; i++){
      if(i != myGameState->whoseTurn){
	printf("Player %d has %d cards in their hand, expected %d\n", i+1, myGameState->handCount[i], newHandCount[i]+1);
	if(myGameState->handCount[i] != (newHandCount[i] + 1)){//check if other players did not gain a card 
          printf("Test failed\n");
          fail++;
        }
      }
    } 
    
    if(myGameState->playedCards[myGameState->playedCardCount-1] != council_room){//check if council room was discard
      printf("Council room was not discarded, test failed\n");
      fail++;
    }else{
      printf("Council room was discarded, test passed\n");
    }

    free(myGameState);

    if(fail == 0){    
      printf("All tests passed!\n");
    }
return 0;
}
