//*************************************
//Tests for Outpost Card
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

    printf ("Testing Outpost card...\n");  

    // place smithy card first in deck
    game.hand[0][0] = outpost;

    
    //store current hand count and actions count
    int curHandCount = game.handCount[0];
    int curOutpostFlag = game.outpostPlayed;

    //play the card
    outpostCard(0,&game,0);


  // outpostPlayed should be 1 greater
  if(game.outpostPlayed == curOutpostFlag + 1)
  {
        printf("outpostCard(): passed outpost played\n");
    }
    else
    {
        printf("outpostCard(): failed outpost played\n");
  }

  // check that we have one less card in the deck
  if(game.handCount[0] == curHandCount - 1)
  {
        printf("outpostCard(): passed hand count\n");
    }
    else
    {
        printf("outpostCard(): failed hand count\n");
  }
  return 0; 
}
