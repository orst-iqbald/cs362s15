//*************************************
//Tests for Smithy Card
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

    printf ("Testing Smithy card...\n");  

    // place smithy card first in deck
    game.hand[0][0] = smithy;
    
    //store current hand count
    int curHandCount = game.handCount[0];

    //play the card
    smithyCard(0,&game,0);

  // check that we have 2 extra cards in hand: draw 3 and discard 1
  if(game.handCount[0] == curHandCount + 2 )
  {
        printf("smithyCard(): passed hand count\n");
    }
    else
    {
        printf("smithyCard(): failed hand count\n");
  }
  return 0; 
}
