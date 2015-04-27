//*************************************
//Tests for Great Hall Card
//************************************

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

    int seed = 1000;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};

    // start building game state
    struct gameState game;
    initializeGame(2, k, seed, &game);

    printf ("Testing Great Hall card...\n");  

    // place smithy card first in deck
    game.hand[0][0] = great_hall;

    
    //store current hand count and actions count
    int curHandCount = game.handCount[0];
    int curNumActions = game.numActions;

    //play the card
    great_hallCard(0,&game,0);


  // numActions should be 2
  if(game.numActions == curNumActions)
  {
        printf("great_hallCard(): passed num actions\n");
    }
    else
    {
        printf("great_hallCard(): failed num actions\n");
  }

  // check that we have same amount of cards in hand: draw card + discard card
  if(game.handCount[0] == curHandCount)
  {
        printf("great_hallCard(): passed hand count\n");
    }
    else
    {
        printf("great_hallCard(): failed hand count\n");
  }
  return 0; 
}
