#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
// cardtest1.c test the smihy card
int main(){

    int fail = 0;
    int newHandCount, numCards, np;
    int seed = 1000;
    int numberPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
      
    struct gameState *myGameState = malloc(sizeof(struct gameState));
    initializeGame(numberPlayers, cards, seed, myGameState);
     
    np = myGameState->whoseTurn;

    for(np = 0; np < numberPlayers; np++){    
      myGameState->whoseTurn = np; 
      newHandCount = myGameState->handCount[np];
      printf("Currentpayer is %d\n", np+1);
      printf("Deck count for player %d is %d\n", np+1, myGameState->deckCount[np]);
      printf("Number of cards in hand is %d\n", numHandCards(myGameState));

      myGameState->hand[np][0] = smithy;
      newSmithy(np, myGameState, 0);

      printf("%d cards in hand after smithy card played!\n", numHandCards(myGameState));

      numCards = 0;

      printf("Deck count after smithy card played for player %d is %d\n", np+1, myGameState->deckCount[np]);
      printf("Number of cards after smithy for player %d is %d\n", np+1,  myGameState->handCount[np]);

      printf("Card name value in played pile %d, expected %d\n", (myGameState->playedCards[myGameState->playedCardCount-1]), smithy);
      if(myGameState->playedCards[myGameState->playedCardCount-1] != smithy){//check if smithy card is in discard pile
	printf("Test Failed\n");
	fail++;
      }      
    
      printf("Hand count after smithy card played is %d, expected %d\n", myGameState->handCount[np], newHandCount+2);
      if(myGameState->handCount[np] != newHandCount+2){//check if 2 cards were added (3 and 1 discarded)      
    	printf("Test Failed\n");
	fail++;
      }
    }   

      free(myGameState);

      if(fail == 0){
	printf("All tests passed!\n");
      }
return 0;
}
